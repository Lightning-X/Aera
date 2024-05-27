#include "renderer.h"
#include "gui/gui.h"

void createImFont(ImFontAtlas* Atlas, ImFont*& font, fs::path path, float size, ImFontConfig* config) {
	font = Atlas->AddFontFromFileTTF(path.string().c_str(), size, config);
}
template <size_t dataSize>
void createImFont(ImFontAtlas* Atlas, ImFont*& font, uint8_t(&Data)[dataSize], float size, ImFontConfig* config) {
	font = Atlas->AddFontFromMemoryTTF(Data, dataSize, size, config);
}
renderer::renderer() : m_swapchain(*pointers::g_swapChain) {
	m_wndProc = WNDPROC(SetWindowLongPtrA(pointers::g_hwnd, GWLP_WNDPROC, LONG_PTR(&renderer::wndProc)));
	if (FAILED(m_swapchain->GetDevice(__uuidof(ID3D11Device), (void**)m_device.GetAddressOf())))
		throw std::runtime_error("Failed to get the D3D device!");
	m_device->GetImmediateContext(m_context.GetAddressOf());
	ImGui::CreateContext();
	ImGui_ImplDX11_Init(m_device.Get(), m_context.Get());
	ImGui_ImplWin32_Init(pointers::g_hwnd);
	ImGui::StyleColorsClassic();
	static auto&& io{ ImGui::GetIO() };
	fs::path path{ fs::path("C:").append("Windows").append("Fonts") };
	fs::path resourcePath{ fs::path(std::getenv("appdata")).append(BRAND).append("Resources") };
	ImFontAtlas* Atlas{ ImGui::GetIO().Fonts };
	float globalSize{ 80.f };
	m_fontCfg.FontDataOwnedByAtlas = false;
	createImFont(Atlas, m_arial, fs::path(path).append("Arial.ttf"), globalSize, &m_fontCfg);
	createImFont(Atlas, m_arialBold, fs::path(path).append("ArialBD.ttf"), globalSize, &m_fontCfg);
	createImFont(Atlas, m_arialBoldItalic, fs::path(path).append("ArialBI.ttf"), globalSize, &m_fontCfg);
	createImFont(Atlas, m_arialBlack, fs::path(path).append("AriBLK.ttf"), globalSize, &m_fontCfg);
	createImFont(Atlas, m_arialItalic, fs::path(path).append("ArialI.ttf"), globalSize, &m_fontCfg);
	createImFont(Atlas, m_tahoma, fs::path(path).append("Tahoma.ttf"), globalSize, &m_fontCfg);
	createImFont(Atlas, m_impact, fs::path(path).append("Impact.ttf"), globalSize, &m_fontCfg);
	io.FontAllowUserScaling = true;
}
renderer::~renderer() {
	SetWindowLongPtrA(pointers::g_hwnd, GWLP_WNDPROC, LONG_PTR(m_wndProc));
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void renderer::onPresent() {
	ui::draw();
}

LRESULT renderer::wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (g_renderer.get()) {
		if (ImGui::GetCurrentContext())
			ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return CallWindowProcA(g_renderer->m_wndProc, hWnd, uMsg, wParam, lParam);
	}
	return -1;
}