#include "VEHHook.hpp"

std::vector<VEHHook::Hook> VEHHook::m_HookTable;

VEHHook::VEHHook()
{
	try
	{
		m_pVectoredHandle = AddVectoredExceptionHandler(1, &VEHHook::VectoredHandler);

		if (m_pVectoredHandle == NULL)
			throw std::runtime_error("Could not add Vectored Exception Handler");
	}
	catch (const std::runtime_error& e)
	{
		throw e;
	}
}


VEHHook::~VEHHook()
{
	if (!m_HookTable.empty()) RemoveAll();
	RemoveVectoredExceptionHandler(m_pVectoredHandle);
}

bool VEHHook::AddHook(PBYTE pEntry, PBYTE pHookFunction)
{
	Hook* newHook = new Hook(pEntry, pHookFunction);

	DWORD dwOld;
	VirtualProtect(newHook->m_Orig, 1, PAGE_EXECUTE_READWRITE, &dwOld);
	newHook->m_OpCode = *newHook->m_Orig;
	printf("Original opcode: 0x%2X\n", newHook->m_OpCode);
	*newHook->m_Orig = INT3;
	VirtualProtect(newHook->m_Orig, 1, dwOld, &dwOld);

	m_HookTable.push_back(*newHook);
	return true;
}

void VEHHook::RemoveHook(PBYTE pEntry)
{
	DWORD dwOld;
	for (Hook& hook : m_HookTable)
	{
		if (hook.m_Orig != pEntry) continue;

		VirtualProtect(hook.m_Orig, 1, PAGE_EXECUTE_READWRITE, &dwOld);
		*hook.m_Orig = hook.m_OpCode;
		VirtualProtect(hook.m_Orig, 1, dwOld, &dwOld);

		m_HookTable.erase(
			std::remove(m_HookTable.begin(), m_HookTable.end(), hook),
			m_HookTable.end()
		);
	}
}

void VEHHook::RemoveAll()
{
	for (Hook& hook : m_HookTable)
		RemoveHook(hook.m_Orig);

	m_HookTable.clear();
}

LONG CALLBACK VEHHook::VectoredHandler(_In_ PEXCEPTION_POINTERS pExceptionInfo)
{
#ifdef _WIN64
#define XIP Rip
#else
#define XIP Eip
#endif

	printf("Exception 0x%X\n", pExceptionInfo->ExceptionRecord->ExceptionCode);

	if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT)
	{
		for (Hook& hook : m_HookTable)
		{
			if (pExceptionInfo->ContextRecord->XIP != (DWORD)hook.m_Orig)
				continue;

			pExceptionInfo->ContextRecord->XIP = (DWORD)hook.m_Detour;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
	}

	return EXCEPTION_CONTINUE_SEARCH;
}