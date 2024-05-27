#include "interface.h"
#include "renderer/renderer.h"
#include "fiber/pool.h"

namespace ui {
	namespace keys {
		void reset() {
			g_open.m_pressed = false;
			g_enter.m_pressed = false;
			g_back.m_pressed = false;
			g_up.m_pressed = false;
			g_down.m_pressed = false;
			g_left.m_pressed = false;
			g_right.m_pressed = false;
		}
	}
	namespace menu {
		void push(submenu& sub) {
			g_menu = sub;
			g_pushMenu = true;
		}
		void pop() {
			if (g_menus.size() > 1 && g_menus.top().m_name != "Home")
				g_menus.pop();
			else
				g_open = false;
		}
	}
	namespace drawing {
		const ImVec2& getResolution() {
			return ImGui::GetIO().DisplaySize;
		}
		const ImVec2& convertCoordTypes(const ImVec2& pos, bool isDC) {
			if (isDC) {
				return pos / getResolution();
			}
			return pos * getResolution();
		}
		const ImVec2& getTextSize(i32 fontId, float size, const std::string& text, float wrap) {
			Font font{ getFont(fontId) };
			ImVec2 textSize{ font->CalcTextSizeA(font->FontSize * size, FLT_MAX, wrap, text.c_str(), NULL) };
			textSize.x = IM_FLOOR(textSize.x + 0.99999999999f);
			return convertCoordTypes(textSize, true);
		}
		float getTextHeight(i32 fontId, float size, float wrap) {
			ImVec2 textSize{ getTextSize(fontId, size, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", wrap) };
			return textSize.y;
		}
		const ImVec2& getSpriteScale(float size) {
			const ImVec2& res{ getResolution() };
			return { (res.y / res.x) * size, size };
		}
		rage::grcTexture* getGameTexture(sprite sprite) {
			auto data{ sprite.get() };
			return pointers::g_textureStore->FindTexture(data.first, data.second);
		}
		Font getFont(i32 Id) {
			switch (Id) {
			case 1: return g_renderer->m_arial; break;
			case 2: return g_renderer->m_arialBold; break;
			case 3: return g_renderer->m_arialItalic; break;
			case 4: return g_renderer->m_arialBoldItalic; break;
			case 5: return g_renderer->m_arialBlack; break;
			case 7: return g_renderer->m_tahoma; break;
			}
			return g_renderer->m_arial;
		}
		void rectangle(const ImVec2& pos, const ImVec2& size, Color color, bool background) {
			ImDrawList* drawList{ background ? ImGui::GetBackgroundDrawList() : ImGui::GetForegroundDrawList() };
			const ImVec2& scaledPos{ convertCoordTypes(pos) };
			const ImVec2& scaledSize{ convertCoordTypes(size) };
			const ImVec2& finalPos{ scaledPos - (scaledSize / 2.f) };
			drawList->AddRectFilled(finalPos, finalPos + scaledSize, color.pack());
		}
		void text(i32 fontId, const std::string& text, ImVec2 pos, float size, Color color, eJustify justify, float padding, float wrap) {
			ImDrawList* drawList{ ImGui::GetForegroundDrawList() };
			const ImVec2& scaledWrap{ convertCoordTypes({ wrap, wrap }) };
			Font font{ getFont(fontId) };
			switch (justify) {
			case eJustify::Left: {
				pos.x = pos.x - (wrap / padding);
			} break;
			case eJustify::Right: {
				const ImVec2& textSize{ getTextSize(fontId, size, text, scaledWrap.y) };
				pos.x = pos.x + (wrap / padding);
				pos.x -= textSize.x;
			} break;
			case eJustify::Center: {
				const ImVec2& textSize{ getTextSize(fontId, size, text, scaledWrap.y) };
				pos.x -= textSize.x / 2.f;
			} break;
			}
			ImVec2 scaledPos{ convertCoordTypes(pos) };
			drawList->AddText(font, (font->FontSize * 1.1f) * size, scaledPos, color.pack(), text.data(), NULL, scaledWrap.y);
		}
		void rotatedImage(ShaderResource resource, const ImVec2& pos, const ImVec2& size, Color color, float angle) {
			ImDrawList* drawList{ ImGui::GetForegroundDrawList() };
			if (angle) {
				helpers::rotation::rotateStart(drawList);
			}
			drawList->AddImage(resource, pos, size, {}, { 1,  1 }, color.pack());
			if (angle) {
				helpers::rotation::rotateEnd(drawList, helpers::degreesToRadians(angle));
			}
		}
		void image(ShaderResource resource, const ImVec2& pos, const ImVec2& size, const Color& color, float rotation) {
			ImDrawList* drawList{ ImGui::GetForegroundDrawList() };
			ImVec2 scaledPos{ convertCoordTypes(pos) };
			ImVec2 scaledSize{ convertCoordTypes(size) };
			ImVec2 finalPos{ scaledPos - (scaledSize / 2.f) };
			rotatedImage(resource, finalPos, { finalPos + scaledSize }, color, rotation);
		}
		void image(sprite sprite, const ImVec2& pos, const ImVec2& size, const Color& color) {
			rage::grcTexture* texture{ getGameTexture(sprite) };
			if (texture) {
				const ImVec2& gameSize{ (texture->Size() / getResolution()) };
				image(texture->m_shader, pos, gameSize * size, color, sprite.m_rotation);
			}
		}
	}
	namespace handlers {
		namespace sounds {
			void queue(const soundData& sound) {
				if (sound.m_active) {
					g_fiberPool.add([&] {
						AUDIO::PLAY_SOUND_FRONTEND(-1, sound.m_id.data(), sound.m_set.data(), NULL);
					});
				}
			}
		}
		namespace key {
			void pressed(input& key) {
				if (GetForegroundWindow() == pointers::g_hwnd) {
					static timer t{};
					if (PAD::IS_USING_KEYBOARD_AND_MOUSE(2)) {
						if (GetAsyncKeyState(key.m_key) & 0x1) {
							key.m_pressed = true;
						}
						else if (GetAsyncKeyState(key.m_key) & 0x8000) {
							t.start(key.m_delay * 100);
							if (t.ready())
								key.m_pressed = true;
						}
						else {
							t.reset();
						}
					}
					else {
						if (key.m_secondaryControl == eControl::ControlEmpty) {
							if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(key.m_keyGroup, key.m_control)) {
								key.m_pressed = true;
							}
							else if (PAD::IS_DISABLED_CONTROL_PRESSED(key.m_keyGroup, key.m_control)) {
								t.start(key.m_delay * 100);
								if (t.ready())
									key.m_pressed = true;
							}
							else {
								t.reset();
							}
						}
						else {
							if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(key.m_keyGroup, key.m_control) && PAD::IS_DISABLED_CONTROL_JUST_PRESSED(key.m_keyGroup, key.m_secondaryControl)) {
								key.m_pressed = true;
							}
							else if (PAD::IS_DISABLED_CONTROL_PRESSED(key.m_keyGroup, key.m_control) && PAD::IS_DISABLED_CONTROL_PRESSED(key.m_keyGroup, key.m_secondaryControl)) {
								t.start(key.m_delay * 100);
								if (t.ready())
									key.m_pressed = true;
							}
							else {
								t.reset();
							}
						}
					}
				}
			}
			void check() {
				pressed(keys::g_open);
				pressed(keys::g_enter);
				pressed(keys::g_back);
				pressed(keys::g_up);
				pressed(keys::g_down);
				pressed(keys::g_left);
				pressed(keys::g_right);
			}
			void actions() {
				if (keys::g_open.m_pressed) {
					sounds::queue(g_open ? sounds::g_open : sounds::g_close);
					g_open ^= true;
				}
				if (g_open) {
					if (keys::g_enter.m_pressed) {
						sounds::queue(sounds::g_enter);
						CURRENT_MENU.action(eActionType::Enter);
					}
					if (keys::g_back.m_pressed) {
						sounds::queue(sounds::g_back);
						menu::pop();
					}
					if (keys::g_up.m_pressed) {
						sounds::queue(sounds::g_up);
						CURRENT_MENU.action(eActionType::Up);
					}
					if (keys::g_down.m_pressed) {
						sounds::queue(sounds::g_down);
						CURRENT_MENU.action(eActionType::Down);
					}
					if (keys::g_left.m_pressed) {
						sounds::queue(sounds::g_left);
						CURRENT_MENU.action(eActionType::Left);
					}
					if (keys::g_right.m_pressed) {
						sounds::queue(sounds::g_right);
						CURRENT_MENU.action(eActionType::Right);
					}
				}
			}
		}
	}
}