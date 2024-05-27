#pragma once
#include "pch/pch.h"
#include "methods/vmt.h"
#include "methods/detour.h"
#define CALL(hk, ...) g_hooking->m_##hk##.getOg<pointers::types::##hk##>()(__VA_ARGS__)
#define CALL_DECL(hk, ...) g_hooking->m_##hk##.getOg<decltype(&##hk)>()(__VA_ARGS__)
#define RET_CALL(hk, ...) return CALL(hk, __VA_ARGS__);
#define RET_CALL_DECL(hk, ...) return CALL_DECL(hk, __VA_ARGS__);
#define VMT_CALL(vmt, hook, ...) g_hooking->m_##vmt##.getOg<decltype(&hooks::##hook)>(g_##hook##Index)(__VA_ARGS__)

inline size_t g_swapchainSize{ 19 };
inline size_t g_resizeBuffersIndex{ 13 };
inline size_t g_presentIndex{ 8 };
struct hooks {
	static void* cTaskJumpConstructor(u64 _This, u32 Flags);
	static void* cTaskFallConstructor(u64 _This, u32 Flags);
	static LPVOID convertThreadToFiber(LPVOID param);
	static HRESULT resizeBuffers(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
	static HRESULT present(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);
};
class dynamicFunctionParser {
public:
	dynamicFunctionParser(LPCSTR moduleName, LPCSTR exportName) :
		m_moduleName(moduleName), m_exportName(exportName)
	{
		if (!m_module) {
			m_module = GetModuleHandleA(m_moduleName);
		}
	}
	FARPROC operator*() {
		if (m_module)
			return GetProcAddress(m_module, m_exportName);
		return nullptr;
	}
private:
	LPCSTR m_moduleName{};
	LPCSTR m_exportName{};
	HMODULE m_module{};
};
class hooking {
	friend struct hooks;
public:
	hooking();
	~hooking();
public:
	void enable();
	void disable();
public:
	MinHook m_minhook;
	detour m_cTaskJumpConstructor;
	detour m_cTaskFallConstructor;
	detour m_convertThreadToFiber;
	hookVFT m_DX;
};
inline std::unique_ptr<hooking> g_hooking{};