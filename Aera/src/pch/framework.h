#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define _HAS_STD_BYTE 0
//Windows Includes (SDKs)
#include <winsdkver.h>
#include <sdkddkver.h>
#include <windows.h>
#include <winternl.h>
#include <d3d11.h>
#include <dxgi.h>
#include <Psapi.h>
#include <tlhelp32.h>
#include <cassert>
#include <cinttypes>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <deque>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <map>
#include <unordered_map>
#include <vector>
#include <array>
#include <wrl/client.h>
#include <random>
#include <filesystem>
#include <timeapi.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <regex>
#include <variant>
#pragma comment(lib, "winmm")
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "wldap32")
#pragma comment(lib, "crypt32")
//ImGui Includes
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include "imgui/backends/imgui_impl_win32.h"
//StackWalker Includes
#include "stackwalker/stackwalker.h"
//ImGui Defines
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//Namespace Defines
using namespace std::chrono;
using namespace std::chrono_literals;