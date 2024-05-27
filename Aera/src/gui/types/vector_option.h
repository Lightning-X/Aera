#pragma once
#include "base_option.h"

namespace ui {
	template <typename t>
	class vectorOption : public baseOption {
	public:
		vectorOption(std::string name, std::string description, std::vector<t> value, i64& pos, bool onChange = false, fnptr<void()> action = nullptr) : baseOption(name, description, action), m_value(value), m_pos(&pos), m_onChange(onChange) {}
		vectorOption(std::string name, std::vector<t> value, i64& pos, bool onChange = false, fnptr<void()> action = nullptr) : vectorOption(name, std::string(), value, pos, onChange, action) {}
	public:
		void draw(bool selected) override {
			baseOption::draw(selected);
			g_base -= g_options.m_size;
			std::stringstream str;
			str << *m_value;
			drawing::text(
				g_options.m_font,
				str.str(),
				{ g_pos.x, g_base + (g_options.m_size / 2.f) - (drawing::getTextHeight(g_options.m_font, g_options.m_textSize) / 2.f) },
				g_options.m_textSize,
				g_options.text(selected),
				eJustify::Right,
				g_options.m_padding,
				g_width
			);
			str.clear();
			g_base += g_options.m_size;
		}
		u32 type() override {
			return static_cast<u32>(eOptionTypes::Vector);
		}
		void action(eActionType type) override {
			bool run{};
			switch (type) {
			case eActionType::Left: {
				run = true;
				if (*m_value > m_min)
					*m_value -= m_step;
				else
					*m_value = m_max;
			} break;
			case eActionType::at_Right: {
				run = true;
				if (*m_value < m_max)
					*m_value += m_step;
				else
					*m_value = m_min;
			} break;
			}
			if (m_onChange && run) {
				if (m_action) {
					m_action();
				}
			}
			baseOption::action(type);
		}
	private:
		std::vector<t> m_value{};
		i64* m_pos{};
		bool m_onChange{};
	};
}