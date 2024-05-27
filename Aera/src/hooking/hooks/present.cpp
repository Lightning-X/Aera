#include "hooking/hooking.h"
#include "renderer/renderer.h"

HRESULT hooks::present(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX11_NewFrame();
	ImGui::NewFrame();
	g_renderer->onPresent();
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return VMT_CALL(DX, present, swapChain, syncInterval, flags);
}