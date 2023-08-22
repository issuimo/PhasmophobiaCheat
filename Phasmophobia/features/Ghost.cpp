#include "Ghost.h"
#include "GhostList.h"

auto Ghost::Ghost_StartHuntingTimer_NEW(void* p) -> void {
    if (noHunt) {
        return;
    }
    return HookManager::call(Ghost_StartHuntingTimer_NEW, p);
}

auto Ghost::Ghost_Hunting_NEW(void* p, bool arg, int i, void* p1) -> void {
    if (noHunt) {
        return;
    }
    return HookManager::call(Ghost_Hunting_NEW, p, arg, i, p1);
}

auto Ghost::Ghost_ChangeFavouriteRoomTo_NEW(void* p, void* arg) -> void {
    if (noNewRoom) {
        return;
    }
    return HookManager::call(Ghost_ChangeFavouriteRoomTo_NEW, p, arg);
}

auto Ghost::Ghost_HuntingCloseDoor_NEW(void* p) -> void {
    if (noCloseDoor) {
        return;
    }
    return HookManager::call(Ghost_HuntingCloseDoor_NEW, p);
}

auto Ghost::Ghost_HuntingCloseDoorNetworked_NEW(void* p, void* p1) -> void {
    if (noCloseDoor) {
        return;
    }
    return HookManager::call(Ghost_HuntingCloseDoorNetworked_NEW, p, p1);
}

Ghost::Ghost() : Feature{} {
    HookManager::install(reinterpret_cast<void(*)(void*)>(
        unity::Il2cpp::Method::GetAddress("GhostAI", "StartHuntingTimer", 0)),
        Ghost_StartHuntingTimer_NEW);
    HookManager::install(reinterpret_cast<void(*)(void*, bool, int, void*)>(
        unity::Il2cpp::Method::GetAddress("GhostAI", "Hunting", 3)),
        Ghost_Hunting_NEW);
    HookManager::install(reinterpret_cast<void(*)(void*, void*)>(
        unity::Il2cpp::Method::GetAddress("GhostController", "ChangeFavouriteRoomTo", 1)),
        Ghost_ChangeFavouriteRoomTo_NEW);
    HookManager::install(reinterpret_cast<void(*)(void*)>(
        unity::Il2cpp::Method::GetAddress("Door", "HuntingCloseDoor", 0)),
        Ghost_HuntingCloseDoor_NEW);
    HookManager::install(reinterpret_cast<void(*)(void*, void* )>(
        unity::Il2cpp::Method::GetAddress("Door", "HuntingCloseDoorNetworked", 1)),
        Ghost_HuntingCloseDoorNetworked_NEW);
}

auto Ghost::GetInstance() -> Ghost& {
    static Ghost Instance;
    return Instance;
}

auto Ghost::GetInfo() const -> const GuiInfo& {
    static GuiInfo info{ reinterpret_cast<const char*>(u8"鬼魂"), reinterpret_cast<const char*>(u8"鬼魂设置"), true };
    return info;
}

auto Ghost::Render() -> void {
    ImGui::Checkbox(reinterpret_cast<const char*>(u8"鬼不猎杀"), &noHunt);
    ImGui::SameLine();
    ImGui::Checkbox(reinterpret_cast<const char*>(u8"鬼不换房"), &noNewRoom);
    ImGui::SameLine();
    ImGui::Checkbox(reinterpret_cast<const char*>(u8"猎杀不关门"), &noCloseDoor);
    ImGui::SameLine();
    ImGui::Checkbox(reinterpret_cast<const char*>(u8"修改速度"), &fixSpeed);
    if (fixSpeed) {
        ImGui::SliderFloat(reinterpret_cast<const char*>(u8"速度"), &speed, 0.0F, 20.0F, "%.1f");
    }
}

auto Ghost::Update() -> void {
    const auto ghosts = GhostList::GetGhosts();
    for (const auto ghost : ghosts) {
        try {
            ghost->SetSpeed(fixSpeed ? speed : 1.0);
        }
        catch (...) {}
    }
}

auto Ghost::DrawStatus() -> void {}

auto Ghost::Save(nlohmann::json& json) -> void {
    json["noHunt"] = noHunt;
    json["noNewRoom"] = noNewRoom;
    json["noCloseDoor"] = noCloseDoor;
    json["fixSpeed"] = fixSpeed;
    json["speed"] = speed;
}

auto Ghost::Load(nlohmann::json& json) -> void {
    if (json.contains("noHunt")) {
        noHunt = json["noHunt"];
    }
    if (json.contains("noNewRoom")) {
        noHunt = json["noNewRoom"];
    }
    if (json.contains("noCloseDoor")) {
        noHunt = json["noCloseDoor"];
    }
    if (json.contains("fixSpeed")) {
        noHunt = json["fixSpeed"];
    }
    if (json.contains("speed")) {
        noHunt = json["speed"];
    }
}
