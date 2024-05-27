#include "pch/pch.h"
#include "memory/pointers.h"
#include "renderer/renderer.h"
#include "hooking/hooking.h"
#include "rage/commands/invoker/invoker.h"
#include "fiber/manager.h"
#include "fiber/pool.h"
#include "script/script.h"
#include "commands/commands.h"
#include "exceptions/handler.h"
#include "core/logger.h"

void init() {
    g_logger = std::make_unique<logger>(BRAND" | Developer (0.00.1, b92)");
    exceptions::initExceptionHandler();
    pointers::scanAll();
    while (*pointers::g_loadingScreenState != eLoadingScreenState::Finished) {
        std::this_thread::sleep_for(100ms);
    }
    g_invoker.cache();
    g_fiberPool.create();
    g_renderer = std::make_unique<renderer>();
    g_hooking = std::make_unique<hooking>();
    g_hooking->enable();
    g_manager.add("commands", &commands::onTick);
    g_manager.add("playerManager", &util::network::manager::onTick);
    g_manager.add("script", &script::onTick);
    engine::createThread(&g_manager);
}
void loop() {
    while (g_running) {
        if (GetAsyncKeyState(VK_F12))
            g_running = false;
        std::this_thread::sleep_for(100ms);
    }
}
void uninit() {
    engine::cleanupThreads();
    g_manager.destory();
    g_hooking->disable();
    g_renderer.reset();
    std::this_thread::sleep_for(300ms);
    g_hooking.reset();
    exceptions::uninitExceptionHandler();
    g_logger.reset();
}
DWORD WINAPI entry(LPVOID) {
    init();
    loop();
    uninit();
    FreeLibraryAndExitThread(g_module, 0);
    return NULL;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    g_module = hModule;
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, NULL, &entry, nullptr, NULL, nullptr);
        break;
    }
    return TRUE;
}