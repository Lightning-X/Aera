#include "memory/pointers.h"

namespace pointers {
    void scanAll() {
        g_scrThreadInit = scan("STI", "83 89 ? ? ? ? ? 83 A1 ? ? ? ? ? 80 A1 ? ? ? ? ?").as<decltype(g_scrThreadInit)>();
        g_scrThreadTick = scan("STT", "80 B9 ? ? ? ? ? 8B FA 48 8B D9 74 05").sub(0xF).as<decltype(g_scrThreadTick)>();
        g_scrThreadKill = scan("STK", "48 89 5C 24 ? 57 48 83 EC 20 48 83 B9 ? ? ? ? ? 48 8B D9 74 14").as<decltype(g_scrThreadKill)>();
        g_handleToPointer = scan("HTP", "83 F9 FF 74 31 4C 8B 0D").as<decltype(g_handleToPointer)>();
        g_pointerToHandle = scan("PTH", "48 8D 1C F8 48 8B CB").add(7).call().as<decltype(g_pointerToHandle)>();
        g_readBitbufArray = scan("RBA", "48 89 5C 24 ? 57 48 83 EC 30 41 8B F8 4C").as<decltype(g_readBitbufArray)>();
        g_writeBitbufArray = scan("WBA", "E8 ? ? ? ? 01 7E 08").call().as<decltype(g_writeBitbufArray)>();
        g_readBitsSingle = scan("RBS", "48 8D 54 24 ? 41 C1 E1 03").add(0xF).call().as<decltype(g_readBitsSingle)>();
        g_writeBitsSingle = scan("WBS", "E8 ? ? ? ? 01 6B 10").call().as<decltype(g_writeBitsSingle)>();
        g_cTaskJumpConstructor = scan("CTJC", "48 89 5C 24 ? 89 54 24 10 57 48 83 EC 30 0F 29 74 24").as<decltype(g_cTaskJumpConstructor)>();
        g_cTaskFallConstructor = scan("CTFC", "E8 ? ? ? ? B3 04 08 98 A0").call().as<decltype(g_cTaskFallConstructor)>();
        g_runAsyncModuleRequest = scan("RAMS", "48 89 5C 24 ? 57 48 83 EC ? 0F B6 99").as<decltype(g_runAsyncModuleRequest)>();
        g_hasIntervalElapsed = scan("HIE", "48 89 5C 24 ? 57 48 83 EC ? 8B FA 8B D9 FF 15").as<decltype(g_hasIntervalElapsed)>();
        g_dispatchEvent = scan("DE", "48 83 EC 20 4C 8B 71 50 33 ED").sub(0x19).as<decltype(g_dispatchEvent)>();
        g_scriptVm = scan("SV", "4A 89 3C 39").sub(0x27).call().as<decltype(g_scriptVm)>();
        g_scGetGameInfoIndex = scan("SGGII", "E8 ? ? ? ? 85 C0 78 27 3B 47 14 7D 1E 48 98 48 8B D6 48 69 C8", { "socialclub.dll" }).call().as<decltype(g_scGetGameInfoIndex)>();
        g_joinBySessionInfo = scan("JBSI", "E8 ? ? ? ? 0F B6 CB 84 C0 41 0F 44 CD").call().as<decltype(g_joinBySessionInfo)>();
        g_proccessPackedEvents = scan("PPE", "66 41 83 F9 ? 0F 83").as<decltype(g_proccessPackedEvents)>();
        g_sendEventAck = scan("SEA", "48 8B DA 44 8B CD").add(0x13).call().as<decltype(g_sendEventAck)>();
        g_getNetObject = scan("GNO", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 54 41 55 41 56 41 57 48 83 EC 40 4C 8B EA").add(0x109).call().as<decltype(g_getNetObject)>();
        g_receiveCloneSync = scan("RCS", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 54 41 55 41 56 41 57 48 83 EC 40 4C 8B EA").as<decltype(g_receiveCloneSync)>();
        g_receiveCloneCreate = scan("RCC", "48 8B C4 66 44 89 48").as<decltype(g_receiveCloneCreate)>();
        g_canApplyData = scan("CAD", "E8 ? ? ? ? 84 C0 0F 84 AF 01 00 00 48 8B 03").call().as<decltype(g_canApplyData)>();
        g_getSyncTreeForType = scan("GSTFT", "0F B7 CA 83 F9 07").as<decltype(g_getSyncTreeForType)>();
        g_getEntityAttachedTo = scan("GEAT", "48 83 EC 28 48 8B 51 50 48 85 D2 74 04").as<decltype(g_getEntityAttachedTo)>();
        g_getGamerTaskResult = scan("GGTR", "E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 8B 05 ? ? ? ? 48 8D 4C 24").call().as<decltype(g_getGamerTaskResult)>();
        g_triggerPlayermenuAction = scan("TPA", "48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B D9").as<decltype(g_triggerPlayermenuAction)>();

        g_textureStore = scan("TS", "48 8D 0D ? ? ? ? E8 ? ? ? ? 8B 45 EC 4C 8D 45 F0 48 8D 55 EC 48 8D 0D ? ? ? ? 89 45 F0 E8").mov().as<decltype(g_textureStore)>();
        g_scGameInfo = scan("SGI", "48 8D 05 ? ? ? ? 48 03 F8 44 8B 47 14 48 8D 57 20 E8 ? ? ? ? 85", { "socialclub.dll" }).mov().as<decltype(g_scGameInfo)>();
        g_presenceData = scan("PD", "48 8D 05 ? ? ? ? 48 8B F1 48 89 01 48 83 C1 08 E8 ? ? ? ? 33 ED 48 8D 8E 68 5B 00 00", { "socialclub.dll" }).mov().as<decltype(g_presenceData)>();
        g_friendRegistry = scan("FR", "41 8B F4 3B C5").sub(0xB).lea().as<decltype(g_friendRegistry)>();
        g_scInfo = scan("SI", "48 8B D3 48 8D 4C 24 ? 48 69 D2").sub(7).mov().as<decltype(g_scInfo)>();
        g_networkPlayerMgr = scan("NPM", "48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF").mov().as<decltype(g_networkPlayerMgr)>();
        g_networkObjectMgr = scan("NOM", "48 8B 0D ? ? ? ? 45 33 C0 E8 ? ? ? ? 33 FF 4C 8B F0").mov().as<decltype(g_networkObjectMgr)>();
        g_network = scan("N", "48 8B 0D ? ? ? ? 48 8B D7 E8 ? ? ? ? 84 C0 75 17 48 8B 0D ? ? ? ? 48 8B D7").mov().as<decltype(g_network)>();
        g_pedFactory = scan("PF", "48 8B 05 ? ? ? ? 8A D1").mov().as<decltype(g_pedFactory)>();
        g_replayInterface = scan("RI", "0F B7 44 24 ? 66 89 44 4E").add(0x1C).mov().as<decltype(g_replayInterface)>();
        g_scriptHandlerMgr = scan("SHM", "74 17 48 8B C8 E8 ? ? ? ? 48 8D 0D").add(0xA).mov().as<decltype(g_scriptHandlerMgr)>();
        g_scrProgramTable = scan("SPT", "48 8B 1D ? ? ? ? 41 83 F8 FF").mov().as<decltype(g_scrProgramTable)>();
        g_nativeRegistrationTable = scan("NRT", "40 B6 01 39 79 2C").add(0xC).mov().as<decltype(g_nativeRegistrationTable)>();
        g_swapChain = scan("SC", "48 8B 3D ? ? ? ? 3B C8").mov().as<decltype(g_swapChain)>();
        g_hashTable = scan("MT", "4C 03 05 ? ? ? ? EB 03").mov().as<decltype(g_hashTable)>();
        g_gtaThreads = scan("GT", "F5 8B FD 73").add(5).mov().as<decltype(g_gtaThreads)>();
        g_globals = scan("G", "48 8B 8D ? ? ? ? 4C 8D 4D 08").add(0xB).mov().as<decltype(g_globals)>();
        g_loadingScreenState = scan("LSS", "83 3D ? ? ? ? ? 75 17 8B 43 20 25").lea().add(1).as<decltype(g_loadingScreenState)>();
        g_threadId = scan("TI", "8B 15 ? ? ? ? 48 8B 05 ? ? ? ? FF C2 89 15 ? ? ? ? 48 8B 0C D8").lea().as<decltype(g_threadId)>();
        g_threadCount = scan("TC", "FF 0D ? ? ? ? 48 8B D9 75").lea().as<decltype(g_threadCount)>();
        g_hwnd = FindWindowA("grcWindow", nullptr);
        LOG(Info, "{}/{} pointers found. ({} failed)", g_foundSigCount, g_totalSigCount, g_failedSigCount);
    }
}