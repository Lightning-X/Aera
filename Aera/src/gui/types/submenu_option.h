#pragma once
#include "base_option.h"

namespace ui {
	class submenuOption : public baseOption {
	public:
		submenuOption(std::string name, std::string description, submenu* submenu, fnptr<void()> action = {}) :
			baseOption(name, description, action), m_submenu(submenu) {
		}
		submenuOption(std::string name, submenu* submenu, fnptr<void()> action = {}) :
			submenuOption(name, {}, submenu, action) {
		}
	public:
		void draw(bool selected) override {
			baseOption::draw(selected);
			g_base -= g_options.m_size;
			drawing::image(
				g_options.m_arrow,
				{ g_pos.x + (g_width / g_options.m_padding), g_base + (g_options.m_size / 2.f) },
				g_options.m_arrowSize,
				g_options.arrow(selected)
			);
			g_base += g_options.m_size;
		}
		void action(eActionType Type) override {
			switch (Type) {
			case eActionType::Enter: {
				menu::push(*m_submenu);
			} break;
			}
			baseOption::action(Type);
		}
		u32 type() override {
			return static_cast<u32>(eOptionTypes::Submenu);
		}
	private:
		submenu* m_submenu{};
	};
}