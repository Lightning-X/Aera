#include "pch.h"
#include "core/logger.h"

void stackWalker::OnOutput(LPCSTR szText) {
	std::string text(szText);
	LOG(Stackwalker, "{}", text.substr(0, text.size() - 1));
}
void stackWalker::OnLoadModule(LPCSTR img, LPCSTR mod, DWORD64 baseAddr, DWORD size, DWORD result, LPCSTR symType, LPCSTR pdbName, ULONGLONG fileVersion) {
	//StackWalker::OnLoadModule(img, mod, baseAddr, size, result, symType, pdbName, fileVersion);
}
void stackWalker::OnSymInit(LPCSTR szSearchPath, DWORD symOptions, LPCSTR szUserName) {
	//StackWalker::OnSymInit(szSearchPath, symOptions, szUserName);
}
void stackWalker::OnDbgHelpErr(LPCSTR szFuncName, DWORD gle, DWORD64 addr) {
	LOG(Stackwalker, "Error ({}) in {} at 0x{:X}", gle, szFuncName, addr);
}
void stackWalker::OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry) {
	HMODULE gameHmod{ GetModuleHandleA(NULL) };
	std::string offsetStr{ std::format("{}.{}+0x{:X}", entry.moduleName, entry.moduleName == "GTA5" ? "exe" : "dll", entry.offset - (entry.moduleName == "GTA5" ? u64(gameHmod) : 0)) };
#ifdef DEBUG
	if (entry.lineFileName[0]) {
		if (entry.name[0]) {
			LOG(Stackwalker, "{} L{}: {} ({})", entry.lineFileName, entry.lineNumber, entry.name, offsetStr);
		}
	}
	else {
		if (entry.name[0]) {
			LOG(Stackwalker, "{} ({})", entry.name, offsetStr);
		}
		else {
			LOG(Stackwalker, "{}", offsetStr);
		}
	}
#else
	if (!entry.lineFileName[0]) {
		if (entry.name[0]) {
			LOG(Stackwalker, "{} ({})", entry.name, offsetStr);
		}
		else {
			LOG(Stackwalker, "{}", offsetStr);
		}
	}
#endif
}