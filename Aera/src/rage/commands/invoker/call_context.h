#pragma once
#include "rage/classes.h"

class context : public rage::scrThread::Info {
public:
	context() : rage::scrThread::Info(&m_return, 0, m_arugments) {
		reset();
	}
public:
	void reset() {
		m_return = {};
		ParamCount = 0;
		Params = m_arugments;
		memset(m_arugments, NULL, 0);
		BufferCount = 0;
		memset(Orig, NULL, sizeof(Orig));
		memset(Buffer, NULL, sizeof(Buffer));
	}
	template <typename type>
	void push(type value) {
		static_assert(sizeof(type) <= 8);
		rage::scrValue data;
		*(type*)(&data) = value;
		m_arugments[ParamCount++] = data;
	}
	template <>
	void push<Vector3>(Vector3 value) {
		push(value.x);
		push(value.y);
		push(value.z);
	}
	template <typename t>
	t getRetVal() {
		return *reinterpret_cast<t*>((u64)ResultPtr);
	}
	template <>
	void getRetVal<void>() {}
private:
	rage::scrValue m_return{};
	rage::scrValue m_arugments[32]{};
};