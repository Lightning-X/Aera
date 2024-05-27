#pragma once
#include "pch/pch.h"
#include "memory/pointers.h"
#include "rage/classes.h"
#include "rage/commands/list.h"
#include "fiber/fiber.h"

namespace util {
	namespace classes {
		inline CPedFactory* getPedFactory() {
			return *pointers::g_pedFactory;
		}
		inline CReplayInterface* getInterface() {
			return *pointers::g_replayInterface;
		}
		inline CVehicleInterface* getVehicleInterface() {
			return getInterface()->m_vehicle_interface;
		}
		inline CPedInterface* getPedInterface() {
			return getInterface()->m_ped_interface;
		}
		inline CPickupInterface* getPickupInterface() {
			return getInterface()->m_pickup_interface;
		}
		inline CObjectInterface* getObjectInterface() {
			return getInterface()->m_object_interface;
		}
		inline CPed* getPed() {
			return getPedFactory()->m_local_ped;
		}
		inline CPlayerInfo* getPlayerInfo() {
			return getPed()->m_player_info;
		}
		inline rage::rlGamerInfo* getRlGamerInfo() {
			return &getPlayerInfo()->m_gamer_info;
		}
		inline rage::atArray<GtaThread*>& getThreads() {
			return *pointers::g_gtaThreads;
		}
		inline GtaThread* getGtaThread(u32 hash) {
			for (GtaThread* thread : getThreads()) {
				if (thread->m_script_hash == hash) {
					return thread;
				}
			}
			return nullptr;
		}
		inline CGameScriptHandlerNetComponent* getScriptHandlerNetComponet(GtaThread* thr) {
			return thr->m_net_component;
		}
	}
	namespace network {
		inline CNetworkObjectMgr* getObjectMgr() {
			return *pointers::g_networkObjectMgr;
		}
		inline CNetwork* get() {
			return *pointers::g_network;
		}
		namespace friends {
			inline FriendRegistry* getRegistry() {
				return pointers::g_friendRegistry;
			}
			inline FriendList* getList() {
				return getRegistry()->m_friend_list;
			}
			inline FriendInfo* getFriends() {
				return getList()->m_friends;
			}
			inline u32 getFriendCount() {
				return getRegistry()->m_friend_count;
			}
			inline void iterateFriends(std::function<void(u32, bool, FriendInfo*)> cb) {
				for (u32 i{}; i != getFriendCount(); ++i) {
					if (auto fr{ &getFriends()[i] }; fr) {
						cb(i, fr->m_is_joinable, fr);
					}
				}
			}
		}
		namespace socialclub {
			inline ScInfo* getInfo() {
				return pointers::g_scInfo;
			}
			inline std::string getTicket() {
				return getInfo()->m_ticket;
			}
			inline std::string authorizationHeader() {
				return "Authorization: SCAUTH val=\"" + getTicket() + "\"";
			}
			inline ScGame getInfo(ccp id) {
				i32 index{ pointers::g_scGetGameInfoIndex(id, pointers::g_scGameInfo->GetGamesAddress(), pointers::g_scGameInfo->m_id) };
				u64 address{ pointers::g_scGameInfo->GetGamesAddress() + (index * 0x148i64) };
				ScGame game;
				memcpy(game.pad_0000, (void*)address, sizeof(game.pad_0000));
				game.m_string = (char*)(address + 0x40);
				memcpy(game.pad_0048, (void*)address, sizeof(game.pad_0048));
				return game;
			}
			inline const char* getString(const char* id) {
				ScGame table{ getInfo(id) };
				return table.m_string;
			}
		}
		namespace session {
			inline rage::snSession* get() {
				return network::get()->m_game_session_ptr;
			}
			inline rage::snSession* getTransition() {
				return network::get()->m_transition_session_ptr;
			}
			namespace peer {
				inline rage::snPeer* getViaConnectionId(uint8_t conId) {
					return session::get()->m_peers[conId];
				}
			}
		}
		inline CNetGamePlayer* getScriptHostNetGamePlayer() {
			if (GtaThread * thr{ classes::getGtaThread("freemode"_joaat) }) {
				if (CGameScriptHandlerNetComponent * netComponet{ classes::getScriptHandlerNetComponet(thr) }) {
					return netComponet->get_host();
				}
			}
			return nullptr;
		}
		inline bool deserialiseNetMessage(enum eNetMessage& msg, class rage::datBitBuffer& buffer) {
			#define RET_DEAD() { \
				msg = eNetMessage::MsgInvalid; \
				return false; \
			}
			if (buffer.m_flagBits & 2)
				RET_DEAD();
			u32 pos{ (buffer.m_flagBits & 1) == 0 ? buffer.m_curBit : buffer.m_maxBit };
			u32 magic{};
			u32 extended{};
			if (buffer.m_bitsRead + 15 > pos)
				RET_DEAD();
			if (!buffer.ReadDword(&magic, 14))
				RET_DEAD();
			if (magic != 0x3246)
				RET_DEAD();
			if (!buffer.ReadDword(&extended, 1))
				RET_DEAD();
			u32 length{ extended ? 16u : 8u };
			pos = (buffer.m_flagBits & 1) == 0 ? buffer.m_curBit : buffer.m_maxBit;
			if (length + buffer.m_bitsRead <= pos) {
				if (buffer.ReadDword((u32*)&msg, length))
					return true;
			}
			return false;
		}
	}
	namespace natives {
		inline void requestModel(u32 hash) {
			for (i8 i{ 25i8 }; !STREAMING::HAS_MODEL_LOADED(hash) && i; --i) {
				STREAMING::REQUEST_MODEL(hash);
				fiber::current()->sleep();
			}
		}
	}
	inline void async(std::function<void()> callback) {
		std::thread(callback).detach();
	}
	inline bool pressed(i8 key) {
		if (GetForegroundWindow() == pointers::g_hwnd) {
			if (GetAsyncKeyState(key) & 0x1) {
				return true;
			}
		}
		return false;
	}
	inline bool onPress(i8 key, std::function<void()> cb = {}) {
		if (pressed(key)) {
			if (cb) {
				cb();
			}
			return true;
		}
		return false;
	}
	inline void iterateFilesInPath(fs::path path, std::string ext, std::function<void(fs::path, std::string)> cb) {
		if (fs::exists(path)) {
			fs::directory_iterator iterator{ path.string() };
			for (auto&& entry : iterator) {
				if (entry.is_regular_file()) {
					fs::path path{ entry.path() };
					if (path.has_filename() && path.extension() == ext) {
						cb(path, path.filename().string());
					}
				}
			}
		}
	}
	template <typename t>
	inline u64 getPoolObjects(i32 type, i32* arr, i32 arrSize) {
		std::vector<uint64_t> objects{};
		t* inf{};
		switch (type) {
		case 0: {
			inf = (t*)classes::getVehicleInterface();
		} break;
		case 1: {
			inf = (t*)classes::getPedInterface();
		} break;
		case 2: {
			inf = (t*)classes::getObjectInterface();
		} break;
		case 3: {
			inf = (t*)classes::getPickupInterface();
		} break;
		}
		for (int32_t i{}; i != inf->m_count; ++i) {
			if (arrSize == i)
				break;
			objects.push_back(inf->m_list->addr(i));
		}
		for (int32_t i{}; i != objects.size(); ++i) {
			arr[i] = pointers::g_pointerToHandle((rage::CEntity*)objects[i]);
		}
		return objects.size();
	}
	inline std::wstring strToWstr(std::string str) {
		return fs::path(str).wstring();
	}
	inline std::string time(std::string format) {
		char timeBuf[256]{};
		i64 timeSinceEpoch{ std::time(nullptr) };
		tm localtime{};
		localtime_s(&localtime, &timeSinceEpoch);
		strftime(timeBuf, sizeof(timeBuf), format.c_str(), &localtime);
		return timeBuf;
	}
	inline constexpr char const* g_advertisementStrings[]{
		"qq",
		"www.",
		".gg",
		".c",
		"http",
		"/Menu",
		"Money/",
		"Money\\",
		"--->",
		"shopgta5",
		"<b>",
		"P888",
		"gtacash",
		"\xE5\xBE\xAE\xE4\xBF\xA1", //"wechat" - Chinese
		"<font s",
		"sellix.io",
		"plano inicial", //"initial plan" - Spanish
		"rep +",
		"l55.me",
		"\xE5\xBA\x97", //"shop" - Chinese
		"\xE9\x92\xB1", //"money" - Chinese
		"\xE5\x88\xB7", //"make(money)" - Chinese
		"\xE8\x90\x9D\xE8\x8E\x89", //"cute girl" - Chinese
		"\xE5\xA6\x88", //"mother" - Chinese
		"\xE7\xBE\x8E\xE5\xA5\xB3", //"sexy girl" - Chinese
		"\xE5\xBC\xBA\xE5\xA5\xB8", //"rape" - Chinese
		"\xE8\x90\x9D", //"loli" - Chinese
		"\xE6\x8C\x82", //"hack" - Chinese
		"\xE5\x85\x83", //Yen sign
		//Known advertisers
		"wavy",
		"krutka",
		"ItzGoated",
		"warlord",
		"doit#",
		"OrangeMango",
		"Faynx"
	};
	inline bool isSpamMessage(std::string message) {
		for (auto& string : g_advertisementStrings) {
			if (message.find(string) != std::string::npos)
				return true;
		}
		return false;
	}
	inline bool isInVehicle(CPed* ped, CVehicle* vehicle) {
		if (!ped || !vehicle)
			return false;
		if (vehicle->m_driver == ped)
			return true;
		for (u8 i{}; i != 15; ++i) {
			if (vehicle->m_passengers[i] == ped)
				return true;
		}
		return false;
	}
}