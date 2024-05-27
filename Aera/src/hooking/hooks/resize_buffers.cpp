#include "hooking/hooking.h"

HRESULT hooks::resizeBuffers(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	HRESULT result{};
	ImGui_ImplDX11_InvalidateDeviceObjects();
	result = VMT_CALL(DX, resizeBuffers, swapChain, bufferCount, width, height, newFormat, swapChainFlags);
	if (SUCCEEDED(result)) {
		ImGui_ImplDX11_CreateDeviceObjects();
	}
	return result;
}