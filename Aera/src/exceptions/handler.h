#pragma once
#include "pch/pch.h"
#include "disassembler.h"
#include "core/logger.h"

namespace exceptions {
	class exceptionError {
	public:
		exceptionError(int t, std::string_view r) : m_type(t), m_reason(r) {}
		std::string what() {
			return m_reason.data();
		}
		int type() {
			return m_type;
		}
		bool operator()() {
			return !what().empty();
		}
	protected:
		int m_type{};
		std::string_view m_reason{};
	};
	class exceptionType {
	public:
		exceptionType(uint32_t code, const char* str) : m_code(code), m_string(str) {}
		std::string str() {
			return m_string.data();
		}
		uint32_t code() {
			return m_code;
		}
		bool operator()() {
			return !str().empty();
		}
	protected:
		uint32_t m_code{};
		std::string_view m_string{};
	};
	class exceptionContext {
	public:
		exceptionContext(EXCEPTION_POINTERS* exception)
			: m_record(*exception->ExceptionRecord), m_context(*exception->ContextRecord), m_type(m_record.ExceptionInformation[0]), m_deathAddress(m_record.ExceptionInformation[1])
		{
			m_code = m_record.ExceptionCode;
			m_exceptionAddress = (uint64_t)m_record.ExceptionAddress;
		}
	public:
		void printRegisters() {
			LOG(Registers, "RAX: 0x{:X} || RSI: 0x{:X}", m_context.Rax, m_context.Rsi);
			LOG(Registers, "RBX: 0x{:X} || RDI: 0x{:X}", m_context.Rbx, m_context.Rdi);
			LOG(Registers, "RCX: 0x{:X} || RBP: 0x{:X}", m_context.Rcx, m_context.Rbp);
			LOG(Registers, "RDX: 0x{:X} || RSP: 0x{:X}", m_context.Rdx, m_context.Rsp);
			LOG(Registers, "R8:  0x{:X} || R9:  0x{:X}", m_context.R8,  m_context.R9);
			LOG(Registers, "R10: 0x{:X} || R11: 0x{:X}", m_context.R10, m_context.R11);
			LOG(Registers, "R12: 0x{:X} || R13: 0x{:X}", m_context.R12, m_context.R13);
			LOG(Registers, "R14: 0x{:X} || R15: 0x{:X}", m_context.R14, m_context.R15);
		}
	public:
		uint32_t m_code{};
		uint64_t m_exceptionAddress{};
		EXCEPTION_RECORD& m_record;
		CONTEXT& m_context;
		uint64_t m_type{};
		uint64_t m_deathAddress{};
		std::string m_fileoffset{};
	};
	inline size_t g_recoveryCount{};
	extern bool attemptStackRecovery(PEXCEPTION_POINTERS exceptionInfo);
#define PAIR(v) exceptionType(v, #v)
	inline std::array<exceptionType, 62> g_exceptionTypes{
		PAIR(STATUS_WAIT_0),
		PAIR(STATUS_ABANDONED_WAIT_0),
		PAIR(STATUS_USER_APC),
		PAIR(STATUS_TIMEOUT),
		PAIR(STATUS_PENDING),
		PAIR(DBG_EXCEPTION_HANDLED),
		PAIR(DBG_CONTINUE),
		PAIR(STATUS_SEGMENT_NOTIFICATION),
		PAIR(STATUS_FATAL_APP_EXIT),
		PAIR(DBG_REPLY_LATER),
		PAIR(DBG_TERMINATE_THREAD),
		PAIR(DBG_TERMINATE_PROCESS),
		PAIR(DBG_CONTROL_C),
		PAIR(DBG_PRINTEXCEPTION_C),
		PAIR(DBG_RIPEXCEPTION),
		PAIR(DBG_CONTROL_BREAK),
		PAIR(DBG_PRINTEXCEPTION_WIDE_C),
		PAIR(DBG_COMMAND_EXCEPTION),
		PAIR(STATUS_GUARD_PAGE_VIOLATION),
		PAIR(STATUS_DATATYPE_MISALIGNMENT),
		PAIR(STATUS_BREAKPOINT),
		PAIR(STATUS_SINGLE_STEP),
		PAIR(STATUS_LONGJUMP),
		PAIR(STATUS_UNWIND_CONSOLIDATE),
		PAIR(DBG_EXCEPTION_NOT_HANDLED),
		PAIR(STATUS_ACCESS_VIOLATION),
		PAIR(STATUS_IN_PAGE_ERROR),
		PAIR(STATUS_INVALID_HANDLE),
		PAIR(STATUS_INVALID_PARAMETER),
		PAIR(STATUS_NO_MEMORY),
		PAIR(STATUS_ILLEGAL_INSTRUCTION),
		PAIR(STATUS_NONCONTINUABLE_EXCEPTION),
		PAIR(STATUS_INVALID_DISPOSITION),
		PAIR(STATUS_ARRAY_BOUNDS_EXCEEDED),
		PAIR(STATUS_FLOAT_DENORMAL_OPERAND),
		PAIR(STATUS_FLOAT_DIVIDE_BY_ZERO),
		PAIR(STATUS_FLOAT_INVALID_OPERATION),
		PAIR(STATUS_FLOAT_OVERFLOW),
		PAIR(STATUS_FLOAT_STACK_CHECK),
		PAIR(STATUS_FLOAT_UNDERFLOW),
		PAIR(STATUS_INTEGER_DIVIDE_BY_ZERO),
		PAIR(STATUS_INTEGER_OVERFLOW),
		PAIR(STATUS_PRIVILEGED_INSTRUCTION),
		PAIR(STATUS_STACK_OVERFLOW),
		PAIR(STATUS_DLL_NOT_FOUND),
		PAIR(STATUS_ORDINAL_NOT_FOUND),
		PAIR(STATUS_ENTRYPOINT_NOT_FOUND),
		PAIR(STATUS_CONTROL_C_EXIT),
		PAIR(STATUS_DLL_INIT_FAILED),
		PAIR(STATUS_CONTROL_STACK_VIOLATION),
		PAIR(STATUS_FLOAT_MULTIPLE_FAULTS),
		PAIR(STATUS_REG_NAT_CONSUMPTION),
		PAIR(STATUS_HEAP_CORRUPTION),
		PAIR(STATUS_STACK_BUFFER_OVERRUN),
		PAIR(STATUS_INVALID_CRUNTIME_PARAMETER),
		PAIR(STATUS_ASSERTION_FAILURE),
		PAIR(STATUS_ENCLAVE_VIOLATION),
		PAIR(STATUS_INTERRUPTED),
		PAIR(STATUS_THREAD_NOT_RUNNING),
		PAIR(STATUS_ALREADY_REGISTERED),
		PAIR(STATUS_SXS_EARLY_DEACTIVATION),
		PAIR(STATUS_SXS_INVALID_DEACTIVATION)
	};
	inline std::array<exceptionError, 3> g_exceptionErrorReasons{
		exceptionError(0, "a attempt to read an invalid address"),
		exceptionError(1, "a attempt to write to an invalid address"),
		exceptionError(8, "an data exception prevention (DEP)")
	};
	extern std::string getExceptionType(ULONG_PTR type);
	extern LONG CALLBACK onExceptionCallback(PEXCEPTION_POINTERS exceptionInfo);
	extern bool onExceptionCallback_TryExcept(PEXCEPTION_POINTERS exceptionInfo);
	extern LONG CALLBACK exceptionHandler(PEXCEPTION_POINTERS exceptionInfo);
	extern LONG CALLBACK unhandledExceptionHandler(PEXCEPTION_POINTERS exceptionInfo);
	inline PVOID vecExcepHandlerHandle{};
	extern void initExceptionHandler();
	extern void uninitExceptionHandler();
}