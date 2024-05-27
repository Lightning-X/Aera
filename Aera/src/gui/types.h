#pragma once
#include "pch/pch.h"
#include "gui/data.h"
#include <gui/lerping_float.h>

namespace ui {
	class tooltip {
	public:
		tooltip(
			std::string text, i32 font, fp textSize, Color textColor, eJustify textJustify,
			bool enabled = true
		) :
			m_text(text), m_font(font), m_textSize(textSize), m_textColor(textColor), m_textJustify(textJustify),
			m_enabled(enabled)
		{}
	public:
		void draw();
	public:
		std::string m_text{};
		i32 m_font{};
		fp m_textSize{};
		Color m_textColor{};
		eJustify m_textJustify{};
		bool m_enabled{};
	};
	class header {
	public:
		header(
			std::string text, fp size, Color col,
			i32 font, fp textSize, Color textColor, eJustify textJustify,
			bool enabled = true
		) :
			m_text(text), m_size(size), m_color(col),
			m_font(font), m_textSize(textSize), m_textColor(textColor), m_textJustify(textJustify),
			m_enabled(enabled)
		{}
	public:
		void draw();
	public:
		std::string m_text{};
		fp m_size{};
		Color m_color{};
		i32 m_font{};
		fp m_textSize{};
		Color m_textColor{};
		eJustify m_textJustify{};
		bool m_enabled{};
	};
	class subtitle {
	public:
		subtitle(std::string text, fp size, fp padding, Color col,
			i32 font, fp textSize, Color textColor, eJustify textJustify,
			i32 optionFont, fp optionTextSize, Color optionTextColor, eJustify optionTextJustify,
			bool enabled = true
		) :
			m_text(text), m_size(size), m_padding(padding), m_color(col),
			m_font(font), m_textSize(textSize), m_textColor(textColor), m_textJustify(textJustify),
			m_optionFont(optionFont), m_optionTextSize(optionTextSize), m_optionTextColor(optionTextColor), m_optionTextJustify(optionTextJustify),
			m_enabled(enabled)
		{}
	public:
		void draw();
	public:
		std::string m_text{};
		fp m_size{};
		fp m_padding{};
		Color m_color{};
		i32 m_font{};
		fp m_textSize{};
		Color m_textColor{};
		eJustify m_textJustify{};
		i32 m_optionFont{};
		fp m_optionTextSize{};
		Color m_optionTextColor{};
		eJustify m_optionTextJustify{};
		bool m_enabled{};
	};
	class options {
	public:
		options(fp size, fp padding, Color col, Color selectedColor,
			i32 font, fp textSize, Color textColor, Color textSelectedColor, eJustify textJustify,
			fp scrollSpeed,
			i32 breakFont, fp breakTextSize, Color breakTextColor, eJustify breakTextJustify,
			sprite arrow, Color arrowColor, Color arrowSelectedColor, ImVec2 arrowSize,
			sprite toggle, Color toggleColor, Color toggleSelectedColor, ImVec2 toggleSize
		) :
			m_size(size), m_padding(padding), m_color(col), m_selectedColor(selectedColor),
			m_font(font), m_textSize(textSize), m_textColor(textColor), m_textSelectedColor(textSelectedColor), m_textJustify(textJustify),
			m_scrollSpeed(scrollSpeed),
			m_breakFont(breakFont), m_breakTextSize(breakTextSize), m_breakTextColor(breakTextColor), m_breakTextJustify(textJustify),
			m_arrow(arrow), m_arrowColor(arrowColor), m_arrowSelectedColor(arrowSelectedColor), m_arrowSize(arrowSize),
			m_toggle(toggle), m_toggleColor(toggleColor), m_toggleSelectedColor(toggleSelectedColor), m_toggleSize(toggleSize)
		{}
	public:
		void draw();
		Color rect(bool selected) {
			return selected ? m_selectedColor : m_color;
		}
		Color text(bool selected) {
			return selected ? m_textSelectedColor : m_textColor;
		}
		Color arrow(bool selected) {
			return selected ? m_arrowSelectedColor : m_arrowColor;
		}
		Color toggle(bool selected) {
			return selected ? m_toggleSelectedColor : m_toggleColor;
		}
	public:
		fp m_size{};
		fp m_padding{};
		Color m_color{};
		Color m_selectedColor{};
		i32 m_font{};
		fp m_textSize{};
		Color m_textColor{};
		Color m_textSelectedColor{};
		eJustify m_textJustify{};
		fp m_scrollSpeed{};
		i32 m_breakFont{};
		fp m_breakTextSize{};
		Color m_breakTextColor{};
		eJustify m_breakTextJustify{};
		sprite m_arrow{};
		Color m_arrowColor{};
		Color m_arrowSelectedColor{};
		ImVec2 m_arrowSize{};
		sprite m_toggle{};
		Color m_toggleColor{};
		Color m_toggleSelectedColor{};
		ImVec2 m_toggleSize{};
	};
	class footer {
	public:
		footer(
			sprite sprite, fp size, Color col,
			fp spriteSize, Color spriteColor,
			bool enabled = true
		) :
			m_sprite(sprite), m_size(size), m_color(col),
			m_spriteSize(spriteSize), m_spriteColor(spriteColor),
			m_enabled(enabled)
		{}
	public:
		void draw();
		bool defaultSprite() {
			if (!m_sprite.m_dictionary.compare("commonmenu")) {
				if (!m_sprite.m_texture.compare("shop_arrows_upanddown") || !m_sprite.m_texture.compare("arrowright")) {
					return true;
				}
			}
			return false;
		}
	public:
		sprite m_sprite{};
		fp m_size{};
		Color m_color{};
		fp m_spriteSize{};
		Color m_spriteColor{};
		bool m_enabled{};
	};
	class description {
	public:
		description(
			std::string text, fp size, fp height, fp padding, Color col,
			i32 font, fp textSize, Color textColor, eJustify textJustify,
			bool enabled = true
		) :
			m_text(text), m_size(size), m_height(height), m_padding(padding), m_color(col),
			m_font(font), m_textSize(textSize), m_textColor(textColor), m_textJustify(textJustify),
			m_enabled(enabled)
		{}
	public:
		void draw();
	public:
		std::string m_text{};
		fp m_size{};
		fp m_height{};
		fp m_padding{};
		Color m_color{};
		i32 m_font{};
		fp m_textSize{};
		Color m_textColor{};
		eJustify m_textJustify{};
		bool m_enabled{};
	};
}