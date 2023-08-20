#include "Init.h"

#include "features/GhostList.h"
#include "features/PlayerList.h"
#include "features/HighSpeed.h"
#include "features/NoDead.h"


#include <TlHelp32.h>

#include "features/Ghost.h"

auto CreateToolhelp32Snapshot_NEW(unsigned long i, unsigned long arg) -> void* {
     return nullptr;
}

auto FindWindowW_NEW(const wchar_t* arg, const wchar_t* str) -> HWND__* {
    return nullptr;
}

void AntiAntiCheat() {
    HookManager::install(FindWindowW, FindWindowW_NEW);
    HookManager::install(CreateToolhelp32Snapshot, CreateToolhelp32Snapshot_NEW);
}

namespace initSpace {

#define ADD(name) Feature::features[name::GetInstance().GetInfo().tableName].push_back(&name::GetInstance())

    auto Feature::Init() -> void {
        ADD(PlayerList);
        ADD(HighSpeed);
        ADD(NoDead);
        ADD(GhostList);
        ADD(Ghost);
    }
}
