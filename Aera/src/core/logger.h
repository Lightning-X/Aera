#pragma once
#include "pch/pch.h"
#define LOG_DIRECT(c, t, s, ...) g_logger.get()->send(eLogColor::c, t, s, __VA_ARGS__);
#define LOG(t, s, ...) g_logger.get()->send(eLogType::t, s, __VA_ARGS__);

enum class eLogColor : u16 {
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	Intensify = FOREGROUND_INTENSITY,
	White = Red | Green | Blue | Intensify,
	Grey = Intensify,
	LightRed = Red | Intensify,
	LightGreen = Green | Intensify,
	LightBlue = Blue | Intensify
};
inline eLogColor operator|(eLogColor a, eLogColor b) {
	return static_cast<eLogColor>(static_cast<std::underlying_type_t<eLogColor>>(a) | static_cast<std::underlying_type_t<eLogColor>>(b));
}
enum class eLogType : u8 {
	Info,
	Warn,
	Fatal,
	Exception,
	Registers,
	Stackwalker,
	Commands,
	Session,
#ifdef DEBUG
	Debug
#endif
};
class logger {
public:
	logger(std::string title) {
		m_path /= BRAND;
		if (!fs::exists(m_path))
			fs::create_directory(m_path);
		m_path /= "Log.txt";
		m_file.open(m_path.string(), std::ios::out | std::ios::trunc);
		if (!AttachConsole(GetCurrentProcessId()))
			AllocConsole();
		SetConsoleTitleA(title.c_str());
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);
		m_con.open("CONOUT$");
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	}
	~logger() {
		FreeConsole();
		fclose(stdout);
		m_path.clear();
		m_con.close();
		m_file.close();
	}
	template <typename ...arguments>
	void send(eLogColor color, std::string type, std::string fmt, arguments... args) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<u16>(color));
		std::string msg{ std::vformat(fmt, std::make_format_args(args...)) };
		m_con << type << " | " << msg << std::endl;
		m_file << type << " | " << msg << std::endl;
	}
	template <typename ...arguments>
	void send(eLogType type, std::string fmt, arguments... args) {
		switch (type) {
		case eLogType::Info: {
			send(eLogColor::Grey, "Info", fmt, args...);
		} break;
		case eLogType::Warn: {
			send(eLogColor::LightRed, "Warn", fmt, args...);
		} break;
		case eLogType::Fatal: {
			send(eLogColor::Red, "Fatal", fmt, args...);
		} break;
		case eLogType::Exception: {
			send(eLogColor::LightRed, "Exception", fmt, args...);
		} break;
		case eLogType::Registers: {
			send(eLogColor::Grey, "Registers", fmt, args...);
		} break;
		case eLogType::Stackwalker: {
			send(eLogColor::LightRed, "StackWalker", fmt, args...);
		} break;
		case eLogType::Commands: {
			send(eLogColor::White, "Commands", fmt, args...);
		} break;
		case eLogType::Session: {
			send(eLogColor::White, "Session", fmt, args...);
		} break;
#ifdef DEBUG
		case eLogType::Debug: {
			send(eLogColor::White, "Debug", fmt, args...);
		} break;
#endif
		default: {
		} break;
		}
	}
private:
	fs::path m_path{ std::getenv("appdata") };
	std::ofstream m_con{};
	std::ofstream m_file{};
};
inline std::unique_ptr<logger> g_logger{};