#include "pch/pch.h"
#include "gui.h"
#include "interface.h"
#include "types/option.h"

namespace ui {
	void tooltip::draw() {
		if (!m_enabled)
			return;
		float pos{ 0.09f };
		float spacing{ 0.03f };
		std::string Keybind{ "Insert or RB + Right" };
		drawing::text(
			m_font,
			m_text,
			{ 0.5f, pos },
			m_textSize,
			m_textColor,
			m_textJustify,
			2.1f,
			-1.f
		);
		drawing::text(
			m_font,
			Keybind,
			{ 0.5f, pos + spacing },
			m_textSize,
			m_textColor,
			m_textJustify,
			2.1f,
			-1.f
		);
	}
	void header::draw() {
		if (!m_enabled)
			return;
		drawing::rectangle({ g_pos.x, g_base + (m_size / 2.f) }, { g_width, m_size }, m_color);
		drawing::text(
			m_font,
			m_text,
			{ g_pos.x, g_base + (m_size / 2.f) - (drawing::getTextSize(m_font, m_textSize, m_text).y / 2.f) },
			m_textSize,
			m_textColor,
			m_textJustify,
			2.1f,
			g_width
		);
		g_base += m_size;
	}
	void subtitle::draw() {
		if (!m_enabled)
			return;
		if (m_text != CURRENT_MENU.m_name)
			m_text = CURRENT_MENU.m_name;
		u64 numOptionsCalc{ OPTION_COUNT };
		u64 selectedOptionCalc{ OPTION_INDEX + 1 };
		for (u64 i{}; i != numOptionsCalc; ++i) {
			if (CURRENT_MENU.m_options.at(i)->type() == (u32)eOptionTypes::Break) {
				if (i < OPTION_INDEX + 1) {
					selectedOptionCalc--;
				}
				numOptionsCalc--;
			}
		}
		std::string optionText{ std::format("{}/{}", selectedOptionCalc, numOptionsCalc) };
		//All hail uniform alignment.
		drawing::rectangle({ g_pos.x, g_base + (m_size / 2.f) }, { g_width, m_size }, m_color);
		drawing::text(
			m_font,
			CURRENT_MENU.m_name,
			{ g_pos.x, g_base + (m_size / 2.f) - (drawing::getTextSize(m_font, m_textSize, m_text).y / 2.f) },
			m_textSize,
			m_textColor,
			m_textJustify,
			m_padding,
			g_width
		);
		drawing::text(
			m_optionFont,
			optionText,
			{ g_pos.x, g_base + (m_size / 2.f) - (drawing::getTextSize(m_optionFont, m_optionTextSize, optionText).y / 2.f) },
			m_optionTextSize,
			m_optionTextColor,
			m_optionTextJustify,
			m_padding,
			g_width
		);
		g_base += m_size;
	}
	void options::draw() {
		CURRENT_MENU.handle([] {
			CURRENT_MENU.add(option("No options."));
		});
	}
	void footer::draw() {
		if (!m_enabled)
			return;
		float size{ m_spriteSize };
		if (IS_STACK_VALID && defaultSprite()) {
			if (OPTION_INDEX == 0) {
				m_sprite.m_texture = "arrowright";
				m_sprite.m_rotation = -180.f;
				size *= 1.5f;
			}
			else if (OPTION_INDEX + 1 == OPTION_COUNT) {
				m_sprite.m_texture = "arrowright";
				m_sprite.m_rotation = 360.f;
				size *= 1.5f;
			}
			else {
				m_sprite.m_texture = "shop_arrows_upanddown";
				m_sprite.m_rotation = 0.f;
				size *= 1.f;
			}
		}
		drawing::rectangle({ g_pos.x, g_base + (m_size / 2.f) }, { g_width, m_size }, m_color);
		drawing::image(m_sprite, { g_pos.x, g_base + (m_size / 2.f) }, { size, size }, m_spriteColor);
		g_base += m_size;
	}
	void description::draw() {
		if (!m_enabled)
			return;
		if (VALID_OPTION)
			m_text = CURRENT_OPTION.m_description;
		if (m_text.empty())
			return;
		g_base += m_height;
		float size{ drawing::getTextSize(m_font, m_textSize, m_text).y + 0.005f };
		drawing::rectangle({ g_pos.x, g_base + (size / 2.f) }, { g_width, size }, m_color);
		drawing::text(
			m_font,
			m_text,
			{ g_pos.x, g_base + (m_size / 2.f) - (drawing::getTextSize(m_font, m_textSize, m_text).y / 2.f) },
			m_textSize,
			m_textColor,
			m_textJustify,
			m_padding,
			g_width
		);
		g_base += size;
	}
	void draw() {
		if (IS_STACK_VALID) {
			handlers::key::actions();
			if (g_open) {
				g_base = g_pos.y;
				g_header.draw();
				g_subtitle.draw();
				g_options.draw();
				g_footer.draw();
				g_description.draw();
			}
			else {
				g_tooltip.draw();
			}
			keys::reset();
		}
		if (g_pushMenu) {
			g_menus.push(g_menu);
			g_pushMenu = false;
		}
	}
}