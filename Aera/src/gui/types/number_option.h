#pragma once
#include "base_option.h"

namespace ui {
	template <typename t>
	class numberOption : public baseOption {
	public:
		numberOption(std::string name, std::string description, t& value, t min, t max, t step = t(1), bool onChange = false, fnptr<void()> action = nullptr) : baseOption(name, description, action), m_value(&value), m_min(min), m_max(max), m_onChange(onChange), m_step(step) {}
		numberOption(std::string name, t& value, t min, t max, t step = t(1), bool onChange = false, fnptr<void()> action = nullptr) : numberOption(name, std::string(), value, min, max, step, onChange, action) {}
	public:
		void draw(bool selected) override {
			baseOption::draw(selected);
			g_base -= g_options.m_size; //Cursed, but functional
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
			return static_cast<u32>(eOptionTypes::Number);
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
			case eActionType::Right: {
				run = true;
				if (*m_value < m_max)
					*m_value += m_step;
				else
					*m_value = m_min;
			} break;
			}
			if (m_onChange && run) {
				baseOption::invoke();
			}
			baseOption::action(type);
		}
	private:
		t* m_value{};
		t m_min{};
		t m_max{};
		t m_step{};
		bool m_onChange{};
	};
}