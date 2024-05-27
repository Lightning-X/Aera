#include "pch/pch.h"
#include "commands.h"
#include "fiber/fiber.h"
#include "util/util.h"
#include "util/clipboard.h"
#include "features.h"
#include "gui/gui.h"
#include "renderer/renderer.h"

namespace commands {
	void copyText(variadicCommand* command) {
		util::clipboard clipboard{ command->get(0).string };
		clipboard.set();
	}
	void copyScString(variadicCommand* command) {
		g_engine.primitiveExecute("copyText {}", util::network::socialclub::getString(command->get(0).string));
	}
	void printCliboard(actionCommand* command) {
		util::clipboard clipboard{};
		clipboard.get();
		LOG_DIRECT(White, "Clipboard", "{}", clipboard.str());
	}
	void useDirectMatchResult(toggleCommand* command) {
		g_engine.m_useDirectMatchResults = command->get(0).toggle;
	}
	void autoCompleteCommands(toggleCommand* command) {
		g_engine.m_autoComplete = command->get(0).toggle;
	}
	void useFirstCommandOnMultipleResults(toggleCommand* command) {
		g_engine.m_useFirstResultOnTooManyResults = command->get(0).toggle;
	}
	void print(variadicCommand* command) {
		std::string str{ command->m_context.substr(command->m_context.find_first_of(' ') + 1) };
		LOG(Info, str);
	}
	void forceQuitToSp(actionCommand* command) {
		NETWORK::SHUTDOWN_AND_LOAD_MOST_RECENT_SAVE();
	}
	void init() {
		g_manager.add(variadicCommand("copyText", "Copy Text", "Copies text to clipboard", { { eValueType::String } }, copyText, false));
		g_manager.add(variadicCommand("copyScString", "Copy Socialclub String", "Copies a string from socialclub.dll to clipboard", { { eValueType::String } }, copyScString, false));
		g_manager.add(actionCommand("printClipboard", "Print Clipboard", "Prints your clipboard to log", printCliboard));
		g_manager.add(toggleCommand("useDirectMatchResults", "Use Direct Match Results", "When an command is a direct match, it will use that when possible", useDirectMatchResult));
		g_manager.add(toggleCommand("autoCompleteCommands", "Auto Complete Commands", "When a command is still being typed and there is no other results, it will auto complete the command", autoCompleteCommands));
		g_manager.add(toggleCommand("useFirstCommandOnMultipleResults", "Use The First Command On Multiple Results", "When an command has multiple results, it will use the closet resembling command", useFirstCommandOnMultipleResults));
		g_manager.add(variadicCommand("print", "Print", "Prints a string", { { eValueType::String } }, print, false));
		g_manager.add(actionCommand("forceQuitToSp", "Force Quit To Story Mode", "Forcefully quits to SP", forceQuitToSp));
		features::init();
		g_manager.init();
	}
	void onInit() {
		features::onInit();
		"useDirectMatchResults"_TC->get(0).toggle = true;
		"autoCompleteCommands"_TC->get(0).toggle = true;
	}
	void onTick() {
		init();
		onInit();
		while (true) {
			features::onTick();
			g_manager.tick();
			fiber::current()->sleep();
		}
	}
}