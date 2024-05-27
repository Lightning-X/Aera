#pragma once
#include "pch/pch.h"
#include "memory/pointers.h"
#include "rage/commands/list.h"

class renderer {
public:
	renderer();
	~renderer();
public:
	void onPresent();
public:
	static LRESULT wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	ImFontConfig m_fontCfg{};
	ImFont* m_arial{};
	ImFont* m_arialBold{};
	ImFont* m_arialItalic{};
	ImFont* m_arialBoldItalic{};
	ImFont* m_arialBlack{};
	ImFont* m_tahoma{};
	ImFont* m_impact{};
public:
	WNDPROC m_wndProc{};
	comPtr<IDXGISwapChain> m_swapchain{};
	comPtr<ID3D11Device> m_device{};
	comPtr<ID3D11DeviceContext> m_context{};
};
inline std::unique_ptr<renderer> g_renderer{};