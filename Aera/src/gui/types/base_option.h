#pragma once
#include "abstract_option.h"
#include "gui/gui.h"
#include "gui/interface.h"
#include "commands/manager/types.h"

namespace ui {
	class baseOption : public abstractOption {
	public:
		baseOption(std::string name, std::string description, fnptr<void()> action) :
			abstractOption(name, description), m_action(action) {
		}
	public:
		void draw(bool selected) override {
			drawing::rectangle({ g_pos.x, g_base + (g_options.m_size / 2.f) }, { g_width, g_options.m_size }, g_options.m_color, true);
			const auto scrollPosition{ g_base + (g_options.m_size / 2.f) };
			static lerpingFloat scroll(scrollPosition, g_options.m_scrollSpeed / 10.f);
			if (selected) {
				drawing::rectangle({ g_pos.x, scroll.setTarget(scrollPosition).update(g_options.m_scrollSpeed / 10.f).getCurrent() }, { g_width, g_options.m_size }, g_options.m_selectedColor);
			}
			drawing::text(
				g_options.m_font,
				m_name,
				{ g_pos.x, g_base + (g_options.m_size / 2.f) - (drawing::getTextSize(g_options.m_font, g_options.m_textSize, m_name).y / 2.f) },
				g_options.m_textSize,
				g_options.text(selected),
				g_options.m_textJustify,
				g_options.m_padding,
				g_width
			);
			g_base += g_options.m_size;
		}
		void action(eActionType type) override {
			switch (type) {
			case eActionType::Enter: {
				invoke();
			} break;
			}
		}
		void invoke() {
			if (m_action)
				m_action();
		}
	private:
		fnptr<void()> m_action{};
	};
}