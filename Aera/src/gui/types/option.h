#pragma once
#include "base_option.h"
#define coption(f, ...) option(f->m_name, f->m_description, [] { f->run(); });

namespace ui {
	class option : public baseOption {
	public:
		option(std::string name, std::string description, fnptr<void()> action = {}) :
			baseOption(name, description, action) {
		}
		option(std::string name, fnptr<void()> action = {}) :
			option(name, {}, action) {
		}
	public:
		u32 type() override {
			return static_cast<u32>(eOptionTypes::Regular);
		}
	};
}