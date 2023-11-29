#include "MoreXP.h"

auto MoreXP::LevelValues_IsPerfectGame_NEW(unity::Il2cpp::Class* class_) -> bool {
    if (on)
        return true;
    return HookManager::Call(LevelValues_IsPerfectGame_NEW, class_);
}

auto MoreXP::LevelValues_GetInestigationBonusReward_NEW(unity::Il2cpp::Class* class_) -> int {
    return HookManager::Call(LevelValues_GetInestigationBonusReward_NEW, class_) + on ? value : 0;
}

auto MoreXP::LevelValues_CompletedMultiplierChallenge_NEW(unity::Il2cpp::Class* class_) -> bool {
    if (on)
        return true;
    return HookManager::Call(LevelValues_IsPerfectGame_NEW, class_);
}

MoreXP::MoreXP() : Feature{} {
    HookManager::Install(reinterpret_cast<bool(*)(unity::Il2cpp::Class*)>(
        unity::Il2cpp::Method::GetAddress("LevelValues", "IsPerfectGame", 0)),
        LevelValues_IsPerfectGame_NEW);
    HookManager::Install(reinterpret_cast<int(*)(unity::Il2cpp::Class*)>(
        unity::Il2cpp::Method::GetAddress("LevelValues", "GetInestigationBonusReward", 0)),
        LevelValues_GetInestigationBonusReward_NEW);
    HookManager::Install(reinterpret_cast<bool(*)(unity::Il2cpp::Class*)>(
        unity::Il2cpp::Method::GetAddress("LevelValues", "CompletedMultiplierChallenge", 0)),
        LevelValues_CompletedMultiplierChallenge_NEW);
}

auto MoreXP::GetInstance() -> MoreXP& {
    static MoreXP Instance;
    return Instance;
}

auto MoreXP::GetInfo() const -> const GuiInfo& {
    static GuiInfo info{ reinterpret_cast<const char*>(u8"结算"), reinterpret_cast<const char*>(u8"增加奖励"), true };
    return info;
}

auto MoreXP::Render() -> void {
    ImGui::Checkbox(reinterpret_cast<const char*>(u8"启用"), &on);
    if (on) {
        ImGui::SameLine();
        ImGui::SliderInt(reinterpret_cast<const char*>(u8"增加值"), &value, 0.0, 5000000.0);
    }
}

auto MoreXP::Update() -> void {

}

auto MoreXP::DrawStatus() -> void {}

auto MoreXP::Save(nlohmann::json& json) -> void {
    json["MoreXP"] = on;
    json["MoreXPV"] = value;
}

auto MoreXP::Load(nlohmann::json& json) -> void {
    if (json.contains("MoreXP")) {
        on = json["MoreXP"];
    }
    if (json.contains("MoreXPV")) {
        value = json["MoreXPV"];
    }
}