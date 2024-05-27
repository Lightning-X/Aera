#pragma once
#include "classes.h"
#include "joaat.h"
#include "memory/pointers.h"
#include "rage/commands/list.h"
#include "rage/classes.h"

namespace engine {
	inline u32 g_frameCount{};
	class thread : public GtaThread {
	public:
		void init() {
			return pointers::g_scrThreadInit(this);
		}
		virtual void do_run() = 0;
		virtual rage::eThreadState reset(uint32_t script_hash, void* args, uint32_t arg_count) {
			RtlZeroMemory(&m_serialised, sizeof(m_serialised));
			m_serialised.m_state = rage::eThreadState::blocked;
			m_serialised.m_script_hash = script_hash;
			m_serialised.m_min_pc = -1;
			m_serialised.m_max_pc = -1;
			m_serialised.m_priority = 1;
			init();
			m_exit_message = "Normal exit";
			return m_serialised.m_state;
		}
		virtual rage::eThreadState run() {
			auto tls{ rage::tlsContext::get() };
			if (!m_handler) {
				pointers::g_scriptHandlerMgr->attach_thread(this);
				m_safe_for_network_game = true;
			}
			auto ogThr = tls->m_script_thread;
			tls->m_script_thread = this;
			if (m_serialised.m_state != rage::eThreadState::halted && g_frameCount != MISC::GET_FRAME_COUNT()) {
				do_run();
				g_frameCount = MISC::GET_FRAME_COUNT();
			}
			tls->m_script_thread = ogThr;
			return m_serialised.m_state;
		}
		virtual rage::eThreadState tick(uint32_t ops_to_execute) {
			return pointers::g_scrThreadTick(this, ops_to_execute);
		}
		virtual void kill() {
			return pointers::g_scrThreadKill(this);
		}
	};
	template <typename t>
	using pgCollection = rage::atArray<t>;
	template <typename t>
	using pgPtrCollection = rage::atArray<t*>;
	inline std::vector<std::pair<thread*, thread*>> g_ownedThreads;
	inline pgPtrCollection<thread>* getThreadCollection() {
		return (pgPtrCollection<thread>*)pointers::g_gtaThreads;
	}
	inline uint32_t& getThreadID() {
		return *pointers::g_threadId;
	}
	inline uint32_t& getThreadCount() {
		return *pointers::g_threadCount;
	}
	inline void createThread(thread* thread) {
		auto& collection{ *getThreadCollection() };
		auto& id{ getThreadID() };
		auto& count{ getThreadCount() };
		int slot{};
		//Get slot
		for (auto& thr : collection) {
			auto& ser{ thr->m_serialised };
			if (!ser.m_thread_id)
				break;
			slot++;
		}
		bool didWeGetSlot{ slot != collection.size() };
		if (didWeGetSlot) {
			std::string name{ std::format("thr_{}", count + 1) };
			auto& ser{ thread->m_serialised };
			strcpy_s(thread->m_name, name.c_str());
			thread->m_script_hash = rage::joaat(thread->m_name);
			thread->reset(thread->m_script_hash, nullptr, 0);
			thread->m_can_be_paused = false;
			if (!id) {
				id++;
			}
			ser.m_thread_id = id;
			count++;
			id++;
			auto og{ collection[slot] };
			collection[slot] = thread;
			g_ownedThreads.push_back(std::make_pair(thread, og));
			LOG(Info, "Successfully created thread '{}' at id {}", thread->m_name, ser.m_thread_id);
		}
	}
	inline void cleanupThreads() {
		if (g_ownedThreads.empty()) {
			return;
		}
		std::reverse(g_ownedThreads.begin(), g_ownedThreads.end());
		auto& collection{ *getThreadCollection() };
		int slot{};
		for (auto& thr : collection) {
			for (auto& [ownedThr, ogThr] : g_ownedThreads) {
				if (thr == ownedThr) {
					collection[slot] = ogThr;
				}
			}
			slot++;
		}
		g_ownedThreads.clear();
	}
}