#pragma once
#include "pch/pch.h"
#include "rage/classes.h"
#include "gui/types/submenu.h"
#include "gui/types.h"
#include "gui/menu_handler.h"

namespace helpers {
	inline float degreesToRadians(float degrees) {
		//Formula: x * PI/180 = y rad
		return static_cast<float>((static_cast<long double>(degrees) * PI) / 180.L);
	}
	namespace rotation {
		inline i32 g_index{};
		inline void rotateStart(ImDrawList* drawList) {
			g_index = drawList->VtxBuffer.Size;
		}
		inline ImVec2 rotationCenter(ImDrawList* drawList) {
			ImVec2 l{ FLT_MAX, FLT_MAX }, u{ -FLT_MAX, -FLT_MAX };
			const auto& buf = drawList->VtxBuffer;
			for (i32 i{ g_index }; i != buf.Size; ++i) {
				l = ImMin(l, buf[i].pos);
				u = ImMax(u, buf[i].pos);
			}
			return (l + u) / 2.f;
		}
		inline void rotateEnd(ImDrawList* drawList, float rad) {
			ImVec2 center{ rotationCenter(drawList) };
			float s{ std::sin(rad) }, c{ std::cos(rad) };
			center = ImRotate(center, s, c) - center;
			auto& buf{ drawList->VtxBuffer };
			for (int i{ g_index }; i != buf.Size; ++i) {
				buf[i].pos = ImRotate(buf[i].pos, s, c) - center;
			}
		}
	}
}
namespace ui {
	using Font = ImFont*;
	using ShaderResource = ID3D11ShaderResourceView*;
	inline std::vector<ccp> g_dictonaryRequests{};
	inline void addDictionaryRequest(ccp dictionary) {
		for (auto& request : g_dictonaryRequests) {
			if (request == dictionary) {
				return;
			}
		}
		g_dictonaryRequests.push_back(dictionary);
	}
	inline bool g_open{ true };
	namespace keys {
		extern void reset();
		inline input g_open{ VK_INSERT, 20, eControl::ControlScriptRB, eControl::ControlFrontendRight };
		inline input g_enter{ VK_RETURN, 20, eControl::ControlFrontendRright };
		inline input g_back{ VK_BACK, eControl::ControlFrontendDown };
		inline input g_up{ VK_UP, eControl::ControlFrontendUp };
		inline input g_down{ VK_DOWN, eControl::ControlFrontendDown };
		inline input g_left{ VK_LEFT, eControl::ControlFrontendLeft };
		inline input g_right{ VK_RIGHT, eControl::ControlFrontendRight };
	}
	inline bool g_pushMenu{ true };
	inline std::stack<submenu> g_menus{};
	inline submenu g_menu{};
	namespace menu {
		#define CURRENT_MENU g_menus.top()
		#define OPTIONS CURRENT_MENU.m_options
		#define OPTION_INDEX CURRENT_MENU.m_current
		#define OPTION_COUNT OPTIONS.size()
		#define VALID_OPTION OPTION_COUNT && OPTIONS[OPTION_INDEX]
		#define CURRENT_OPTION static_cast<abstractOption&>(*OPTIONS[OPTION_INDEX])
		#define IS_STACK_VALID !g_menus.empty() && g_menus.size() > NULL
		extern void push(submenu& sub);
		extern void pop();
	}
	namespace drawing {
		extern const ImVec2& getResolution();
		extern const ImVec2& convertCoordTypes(const ImVec2& pos, bool isDC = false);
		extern const ImVec2& getTextSize(i32 fontId, float size, const std::string& text, float Wrap = -1.f);
		extern float getTextHeight(i32 fontId, float size, float Wrap = -1.f);
		extern const ImVec2& getSpriteScale(float size);
		extern rage::grcTexture* getGameTexture(sprite sprite);
		extern Font getFont(i32 id);
		extern void rectangle(const ImVec2& pos, const ImVec2& size, Color color, bool background = false);
		extern void text(i32 fontId, const std::string& text, ImVec2 pos, float size, Color color, eJustify justify, float padding, float wrap);
		extern void rotatedImage(ShaderResource resource, const ImVec2& pos, const ImVec2& size, Color color, float angle);
		extern void image(ShaderResource resource, const ImVec2& pos, const ImVec2& size, const Color& color, float rotation = 0.f);
		extern void image(const sprite& sprite, const ImVec2& pos, const ImVec2& size, const Color color);
	}
	namespace handlers {
		namespace sounds {
			inline soundData g_open{ true, "SELECT" };
			inline soundData g_close{ true, "BACK" };
			inline soundData g_enter{ true, "SELECT" };
			inline soundData g_back{ true, "BACK" };
			inline soundData g_left{ true, "NAV_LEFT_RIGHT" };
			inline soundData g_right{ true, "NAV_LEFT_RIGHT" };
			inline soundData g_up{ true, "NAV_UP_DOWN" };
			inline soundData g_down{ true, "NAV_UP_DOWN" };
			extern void queue(const soundData& sound);
		}
		namespace key {
			extern void pressed(input& key);
			extern void check();
			extern void actions();
		}
	}
}