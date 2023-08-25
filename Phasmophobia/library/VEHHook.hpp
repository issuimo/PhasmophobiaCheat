#pragma once
#include <Windows.h>
#include <vector>
#include <mutex>
#include <algorithm>

#define TRAP_FLAG (1 << 8)
#define INT3	0xCC;

class VEHHook
{
public:
	VEHHook();
	~VEHHook();
	bool AddHook(PBYTE pEntry, PBYTE pHookFunction);
	void RemoveHook(PBYTE pEntry);
	void RemoveAll();

	struct Hook
	{
		PBYTE m_Orig;
		PBYTE m_Detour;
		BYTE  m_OpCode;

		Hook() { m_Orig = m_Detour = 0; }
		Hook(PBYTE dwOrig, PBYTE dwDetour)
		{
			m_Orig = dwOrig;
			m_Detour = dwDetour;
		}

		friend bool operator==(const Hook& _h1, const Hook& _h2)
		{
			return _h1.m_Orig == _h2.m_Orig;
		}
	};
private:
	PVOID m_pVectoredHandle;
	static LONG CALLBACK VectoredHandler(_In_ PEXCEPTION_POINTERS);
	static std::vector<Hook> m_HookTable;
};
