#pragma once
#include "pch/pch.h"
#include "rage/engine.h"
#include "fiber.h"

class manager : public engine::thread {
public:
	void add(char const* id, fnptr<void()> fn, bool log = true, std::optional<std::size_t> stackSize = std::nullopt) {
		std::lock_guard lck(m_mutex);
		m_fibers.insert({ id, std::make_unique<fiber>(fn, stackSize) });
		if (log)
			LOG(Info, "Created fiber {}", id);
	}
	void add(char const* id, int count, fnptr<void()> fn, std::optional<std::size_t> stackSize = std::nullopt) {
		for (int32_t i{ count }; i; --i) {
			add(std::format("{}_{}", id, i).c_str(), fn, false, stackSize);
		}
		LOG(Info, "Created fiber group '{}' with {} fibers", id, count);
	}
	void remove(char const* id) {
		std::lock_guard lck(m_mutex);
		m_fibers.erase(id);
	}
	void destory() {
		std::lock_guard lck(m_mutex);
		m_fibers.clear();
	}
	void do_run() override {
		static bool ensureMainFiber = (ConvertThreadToFiber(nullptr), true);
		std::lock_guard lck(m_mutex);
		for (auto& scr : m_fibers) {
			scr.second->tick();
		}
	}
private:
	std::recursive_mutex m_mutex{};
	std::map<char const*, std::unique_ptr<fiber>> m_fibers{};
};
inline manager g_manager{};