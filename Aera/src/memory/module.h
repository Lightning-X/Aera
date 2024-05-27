#pragma once
#include "pch/pch.h"
#include "mem.h"

class hmodule {
public:
	hmodule(std::string_view name = {}) : m_name(name), m_handle(get()), m_base(m_handle) {
		auto dosHeader = m_base.as<IMAGE_DOS_HEADER*>();
		auto ntHeader = m_base.add(dosHeader->e_lfanew).as<IMAGE_NT_HEADERS*>();
		m_size = ntHeader->OptionalHeader.SizeOfImage;
	}
public:
	mem begin() {
		return m_base;
	}
	mem end() {
		return begin().add(size());
	}
	size_t size() {
		return m_size;
	}
public:
	FARPROC getProcess(std::string search) {
		return GetProcAddress(m_handle, search.c_str());
	}
	HMODULE get() {
		if (m_name.empty())
			return GetModuleHandleA(NULL);
		return GetModuleHandleA(m_name.data());
	}
private:
	std::string_view m_name{};
	HMODULE m_handle{};
	mem m_base{};
	size_t m_size{};
};