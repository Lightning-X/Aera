#include "pool.h"

void fiberPool::create() {
	g_manager.add("FiberPool", m_numberOfFibers, &routine);
}

void fiberPool::add(std::function<void()> func) {
	if (func) {
		std::lock_guard lck(m_mutex);
		m_jobs.push(std::move(func));
	}
}

void fiberPool::tick() {
	std::unique_lock lck(m_mutex);
	if (!m_jobs.empty()) {
		auto job = m_jobs.top();
		if (job) {
			m_jobs.pop();
			lck.unlock();
			job();
		}
	}
}

void fiberPool::routine() {
	while (true) {
		g_fiberPool.tick();
		fiber::current()->sleep();
	}
}