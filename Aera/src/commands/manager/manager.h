#pragma once
#include "commands/manager/types.h"

namespace commands {
	class manager {
	public:
		template <typename t>
		void add(t command) {
			t* cmd{ new t(command) };
			m_commands.insert({ cmd->id(), std::move(cmd) });
		}
		void remove(ccp id);
		void init();
		void tick();
		void clear();

		template <typename t>
		t* getCommand(cc* id) {
			for (auto& e : m_commands) {
				auto& c{ e.second };
				if (c->m_id == id) {
					return (t*)c;
				}
			}
			return nullptr;
		}
		std::map<ccp, abstractCommand*>& getCommands() {
			return m_commands;
		}
	private:
		std::map<ccp, abstractCommand*> m_commands{};
	};
	inline manager g_manager{};
}
inline commands::abstractCommand* operator ""_ABC(const char* str, size_t) {
	return commands::g_manager.getCommand<commands::abstractCommand>(str);
}
inline commands::toggleCommand* operator ""_TC(const char* str, size_t) {
	return commands::g_manager.getCommand<commands::toggleCommand>(str);
}
inline commands::intCommand* operator ""_IC(const char* str, size_t) {
	return commands::g_manager.getCommand<commands::intCommand>(str);
}
inline commands::toggleIntCommand* operator ""_TIC(const char* str, size_t) {
	return commands::g_manager.getCommand<commands::toggleIntCommand>(str);
}
inline commands::floatCommand* operator ""_FC(const char* str, size_t) {
	return commands::g_manager.getCommand<commands::floatCommand>(str);
}
inline commands::toggleFloatCommand* operator ""_TFC(const char* str, size_t) {
	return commands::g_manager.getCommand<commands::toggleFloatCommand>(str);
}
inline commands::actionCommand* operator ""_AC(const char* str, size_t) {
	return commands::g_manager.getCommand<commands::actionCommand>(str);
}
inline commands::protectionCommand* operator ""_PC(const char* str, size_t) {
	return commands::g_manager.getCommand<commands::protectionCommand>(str);
}
inline commands::sectionProtectionCommand* operator ""_SPC(const char* str, size_t) {
	return commands::g_manager.getCommand<commands::sectionProtectionCommand>(str);
}
inline commands::variadicCommand* operator ""_VC(const char* str, size_t) {
	return commands::g_manager.getCommand<commands::variadicCommand>(str);
}