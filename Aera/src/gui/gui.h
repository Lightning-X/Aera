#pragma once
#include "pch/pch.h"
#include "types.h"

namespace ui {
	extern void draw();
	inline tooltip g_tooltip{ "Imagine not having any tooltips", 0, 0.4f, { 0, 186, 255, 255 }, eJustify::Center };
	inline header g_header{ BRAND, 0.1f, { 0, 186, 255, 255 }, 7, 1.f, { 255, 255, 255, 255 }, eJustify::Left };
	inline subtitle g_subtitle{ "", 0.04f, 2.1f, { 0, 0, 0, 220 }, 0, 0.4f, { 255, 255, 255, 255 }, eJustify::Left, 0, 0.4f, { 255, 255, 255, 255 }, eJustify::Right };
	inline options g_options{ 0.04f, 2.1f, { 0, 0, 0, 160 }, { 255, 255, 255, 255 }, 0, 0.35f, { 255, 255, 255, 255 }, { 10, 10, 10, 255 }, eJustify::Left, 6.5f, 1, 0.35f, { 255, 255, 255, 255 }, eJustify::Center, { "commonmenu", "arrowright" }, { 255, 255, 255, 255 }, { 10, 10, 10, 255 }, { 1.3f, 1.3f }, { "timerbars", "circle_checkpoints" }, { 200, 25, 80, 255 }, { 130, 214, 157, 255 }, { 1.4f, 1.4f } };
	inline footer g_footer{ { "commonmenu", "shop_arrows_upanddown" }, 0.04f, { 10, 10, 10, 200 }, 1.f, { 255, 255, 255, 255 } };
	inline description g_description{ "", 0.033f, 0.01f, 2.1f, { 0, 0, 0, 120 }, 0, 0.28f, { 255, 255, 255, 255 }, eJustify::Left };
	inline float g_width{ 0.24f };
	inline ImVec2 g_pos{ 0.8f, 0.1f };
	inline float g_base{};
}