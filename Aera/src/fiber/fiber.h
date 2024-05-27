#pragma once
#include "pch/pch.h"
#include "core/logger.h"

class fiber {
public:
	fiber(fnptr<void()> fn, std::optional<std::size_t> stackSize = std::nullopt) : m_func(fn), m_stackSize(stackSize) {
		create(fn);
	}
	~fiber() {
		destroy();
	}
public:
	void create(fnptr<void()> func) {
		m_fibers.second = CreateFiber(m_stackSize.has_value() ? m_stackSize.value() : 0, &fiber::routine, this);
	}
	void destroy() {
		if (m_fibers.second)
			DeleteFiber(m_fibers.second);
	}
	void sleep(std::optional<std::chrono::high_resolution_clock::duration> time = std::nullopt) {
		if (time.has_value() && time.value() != 0ms)
			m_time = std::chrono::high_resolution_clock::now() + time.value();
		else
			m_time = std::nullopt;
		SwitchToFiber(m_fibers.first);
	}
	void tick() {
		m_fibers.first = GetCurrentFiber();
		if (!m_time.has_value() || m_time.value() <= std::chrono::high_resolution_clock::now())
			SwitchToFiber(m_fibers.second);
	}
	static void routine(PVOID param) {
		fiber& f{ *static_cast<fiber*>(param) };
		try {
			f.m_func();
		}
		catch (std::exception& except) {
			LOG(Exception, "Caught exception {} in a fiber", except.what());
		}
		while (true) {
			f.sleep();
		}
	}
	static fiber* current() {
		return static_cast<fiber*>(GetFiberData());
	}
public:
	std::pair<void*, void*> m_fibers{};
	fnptr<void()> m_func{};
	std::optional<std::chrono::high_resolution_clock::time_point> m_time{};
	std::optional<std::size_t> m_stackSize{};
};