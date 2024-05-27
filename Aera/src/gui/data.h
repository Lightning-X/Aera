#pragma once
#include "pch/pch.h"
#include "rage/enums.h"

namespace ui {
	class Color {
	public:
		Color(i32 r, i32 g, i32 b, i32 a) : _r(r), _g(g), _b(b), _a(a) {}
		Color(fp r, fp g, fp b, fp a) : Color(i32(r) * 255, i32(g) * 255, i32(b) * 255, i32(a) * 255) {}
		Color(bool white = true, bool alpha = true) : Color(white ? 255 : 0, white ? 255 : 0, white ? 255 : 0, alpha ? 255 : 0) {}
	public:
		u32 pack() {
			return _a << 24 | _b << 16 | _g << 8 | _r << 0;
		}
	public:
		const i32 r() { return _r; }
		const fp r_f() { return (r() & 0xFF) / 255.f; }
	public:
		const i32 g() { return _g; }
		const fp g_f() { return (g() & 0xFF) / 255.f; }
	public:
		const i32 b() { return _b; }
		const fp b_f() { return (b() & 0xFF) / 255.f; }
	public:
		const i32 a() { return _a; }
		const fp a_f() { return (a() & 0xFF) / 255.f; }
	private:
		u8 _r;
		u8 _g;
		u8 _b;
		u8 _a;
	};
	enum class eJustify : u8 {
		Left,
		Right,
		Center
	};
	class timer {
	public:
		void start(u64 Time) {
			if (m_tick) {
				m_readyAt = GetTickCount64() + Time;
				m_tick = false;
			}
		}
		bool ready() {
			return GetTickCount64() > m_readyAt;
		}
		void reset() {
			m_tick = true;
		}
	private:
		u64 m_readyAt{};
		bool m_tick{};
	};
	class sprite {
	public:
		std::pair<const char*, const char*> get() {
			return { m_dictionary.c_str(), m_texture.c_str() };
		}
	public:
		std::string m_dictionary{};
		std::string m_texture{};
		fp m_rotation{};
	};
	class soundData {
	public:
		bool m_active{};
		std::string_view m_id{};
		std::string_view m_set{ "HUD_FRONTEND_DEFAULT_SOUNDSET" };
	};
	class input {
	public:
		input(i8 key, u64 delay, eControl control, eControl secondaryControl, i8 keyGroup) :
			m_key(key), m_delay(delay),
			m_control(control), m_secondaryControl(secondaryControl), m_keyGroup(keyGroup)
		{}
		input(i8 key, u64 delay, eControl control, eControl secondaryControl) : input(key, delay, control, secondaryControl, 2) {}
		input(i8 key, u64 delay, eControl control) : input(key, delay, control, eControl::ControlEmpty) {}
		input(i8 key, eControl control) : input(key, 10, control) {}
	public:
		i8 m_key{};
		u64 m_delay{};
		bool m_pressed{};
		eControl m_control{};
		eControl m_secondaryControl{};
		i8 m_keyGroup{ 2 };
		operator bool() {
			return m_pressed;
		}
	};
}