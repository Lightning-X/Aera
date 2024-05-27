#pragma once
#include "manager/manager.h"
#include "engine/engine.h"

namespace commands {
	extern void copyText(variadicCommand* command);
	extern void printCliboard(actionCommand* command);
	extern void useDirectMatchResult(toggleCommand* command);
	extern void autoCompleteCommands(toggleCommand* command);
	extern void useFirstCommandOnMultipleResults(toggleCommand* command);
	extern void print(variadicCommand* command);
	extern void forceQuitToSp(actionCommand* command);
	extern void init();
	extern void onInit();
	extern void onTick();
}