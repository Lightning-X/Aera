#include "hooking/hooking.h"

LPVOID hooks::convertThreadToFiber(LPVOID param) {
	if (IsThreadAFiber())
		return GetCurrentFiber();
	RET_CALL_DECL(convertThreadToFiber, param);
}