#include <cstdio>

#define DLL \
    extern "C" __declspec(dllexport)

auto __stdcall DllMain(void* hModule, int ul_reason_for_call, int lpReserved) -> int {
    switch (ul_reason_for_call) {
        case 1:
            printf("\a");
        case 2:
        case 3:
        case 0:
            break;
    }
    return 1;
}

DLL __int64 __fastcall AddExceptionReceived(__int64 a1) { return 0; }

DLL __int64 __fastcall AddExited(__int64 a1, __int64 a2, int a3) { return 0; }

DLL __int64 __fastcall AddOutputDataReceived(__int64 a1, __int64 a2, int a3) { return 0; }

DLL __int64 __fastcall BeginOutputReadLine(__int64 a1) { return 0; }

DLL __int64 __fastcall CancelOutputRead(__int64 a1) { return 0; }

DLL __int64 CreateProcess() { return 0; }

DLL __int64 CreateProcessStartInfo() { return 0; }

DLL __int64 __fastcall DisposeProcess(__int64 a1) { return 0; }

DLL __int64 __fastcall DisposeProcessStartInfo(__int64 a1) { return 0; }

DLL __int64 __fastcall DotNetRuntimeDebugHeader() { return 0; }

DLL __int64 __fastcall Free(unsigned __int64 a1) { return 0; }

DLL __int64 __fastcall FreeGCHandle(__int64 a1) { return 0; }

DLL __int64 __fastcall GetArguments(__int64 a1) { return 0; }

DLL __int64 __fastcall GetCreateNoWindow(__int64 a1) { return 0; }

DLL __int64 __fastcall GetEnableRaisingEvents(__int64 a1) { return 0; }

DLL const char* __fastcall GetFileName(__int64 a1) { return ""; }

DLL __int64 __fastcall GetProcessExitCode(__int64 a1) { return 0; }

DLL __int64 __fastcall GetProcessExitTime(__int64 a1) { return 0; }

DLL int __stdcall GetProcessId(void* Process) { return 0; }

DLL const char* __fastcall GetProcessName(__int64 a1) { return ""; }

DLL __int64 __fastcall GetProcessStartTime(__int64 a1) { return 0; }

DLL __int64 __fastcall GetProcesses(__int64 a1, __int64 a2) { return 0; }

DLL __int64 __fastcall GetProcessesByName(__int64 a1, __int64 a2, __int64 a3) { return 0; }

DLL __int64 __fastcall GetProcessesByNameString(__int64 a1, __int64 a2, __int64 a3, __int64 a4) { return 0; }

DLL const char* __fastcall GetProcessesString(__int64 a1, __int64 a2, __int64 a3) { return ""; }

DLL const char* __fastcall GetRedirectStandardOutput(__int64 a1) { return ""; }

DLL __int64 __fastcall GetUseShellExecute(__int64 a1) { return 0; }

DLL __int64 __fastcall GetWorkingDirectory(__int64 a1) { return 0; }

DLL __int64 __fastcall Kill(__int64 a1) { return 0; }

DLL __int64 __fastcall KillBool(__int64 a1, unsigned __int8 a2) { return 0; }

DLL __int64 RemoveExceptionReceived() { return 0; }

DLL __int64 __fastcall RemoveExited(__int64 a1, int a2) { return 0; }

DLL __int64 __fastcall RemoveOutputDataReceived(__int64 a1, int a2) { return 0; }

DLL __int64 __fastcall SetArguments(__int64 a1, __int64 a2) { return 0; }

DLL __int64 __fastcall SetCreateNoWindow(__int64 a1, char a2) { return 0; }

DLL __int64 __fastcall SetEnableRaisingEvents(__int64 a1, unsigned __int8 a2) { return 0; }

DLL __int64 __fastcall SetFileName(__int64 a1, __int64 a2) { return 0; }

DLL __int64 __fastcall SetRedirectStandardOutput(__int64 a1, char a2) { return 0; }

DLL __int64 __fastcall SetStartInfo(__int64 a1, __int64 a2) { return 0; }

DLL __int64 __fastcall SetUseShellExecute(__int64 a1, char a2) { return 0; }

DLL __int64 __fastcall SetWorkingDirectory(__int64 a1, __int64 a2) { return 0; }

DLL __int64 __fastcall Start(__int64 a1) { return 0; }

DLL __int64 __fastcall WaitForExit(__int64 a1) { return 0; }

DLL __int64 __fastcall WaitForExitMilliseconds(__int64 a1, unsigned int a2) { return 0; }
