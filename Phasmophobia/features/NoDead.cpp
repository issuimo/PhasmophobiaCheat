#include "NoDead.h"

auto NoDead::Player_StartKillingPlayer_NEW(void* p) -> void {
    if (noDead)
        return;
    return HookManager::call(Player_StartKillingPlayer_NEW, p);
}

auto NoDead::Player_KillPlayer_NEW(void* p, bool v) -> void {
    if (noDead)
        return;
    return HookManager::call(Player_KillPlayer_NEW, p, v);
}

auto NoDead::Player_Dead_NEW(void* p, bool arg, void* po) -> void {
    if (noDead)
        return;
    return HookManager::call(Player_Dead_NEW, p, arg, po);
}

auto NoDead::Player_DeadRoomEffects_NEW(void* p) -> void {
    if (noDead)
        return;
    return HookManager::call(Player_DeadRoomEffects_NEW, p);
}

NoDead::NoDead() : Feature{} {
    HookManager::install(reinterpret_cast<void(*)(void*)>(
                             unity::Il2cpp::Method::GetAddress("Player", "StartKillingPlayer", 0)),
                         Player_StartKillingPlayer_NEW);
    HookManager::install(reinterpret_cast<void(*)(void*, bool)>(
                             unity::Il2cpp::Method::GetAddress("Player", "KillPlayer", 1)),
                         Player_KillPlayer_NEW);
    HookManager::install(reinterpret_cast<void(*)(void*, bool, void*)>(
        unity::Il2cpp::Method::GetAddress("Player", "Dead", 2)),
        Player_Dead_NEW);
    HookManager::install(reinterpret_cast<void(*)(void*)>(
        unity::Il2cpp::Method::GetAddress("Player", "DeadRoomEffects", 0)),
        Player_DeadRoomEffects_NEW);
}

auto NoDead::GetInstance() -> NoDead& {
    static NoDead Instance;
    return Instance;
}

auto NoDead::GetInfo() const -> const GuiInfo& {
    static GuiInfo info{reinterpret_cast<const char*>(u8"玩家"), reinterpret_cast<const char*>(u8"玩家设置"), true};
    return info;
}

auto NoDead::Render() -> void {
    ImGui::Checkbox(reinterpret_cast<const char*>(u8"玩家不死"), &noDead);
}

auto NoDead::Update() -> void { }

auto NoDead::DrawStatus() -> void {}

auto NoDead::Save(nlohmann::json& json) -> void {
    json["noDead"] = noDead;
}

auto NoDead::Load(nlohmann::json& json) -> void {
    if (json.contains("noDead")) {
        noDead = json["noDead"];
    }
}
