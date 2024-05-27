#pragma once
#include "pch/pch.h"
#include "fiber.h"
#include "manager.h"

class fiberPool {
public:
    void create();
    void add(std::function<void()> func);
    void tick();
    static void routine();
private:
    size_t m_numberOfFibers{ 10 };
    std::recursive_mutex m_mutex{};
    std::stack<std::function<void()>> m_jobs{};
};
inline fiberPool g_fiberPool{};