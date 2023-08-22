#include "HighSpeed.h"
#include "PlayerList.h"

HighSpeed::HighSpeed() : Feature{} {
    SetPlayerSpeed = reinterpret_cast<void(*)(void*, float)>(unity::Il2cpp::Method::GetAddress("Player", "SetPlayerSpeed", 1));
}

auto HighSpeed::GetInstance() -> HighSpeed& {
    static HighSpeed Instance;
    return Instance;
}

auto HighSpeed::GetInfo() const -> const GuiInfo& {
    static GuiInfo info{ reinterpret_cast<const char*>(u8"玩家"), reinterpret_cast<const char*>(u8"玩家速度"), true };
    return info;
}

auto HighSpeed::Render() -> void {
    ImGui::Checkbox(reinterpret_cast<const char*>(u8"修改移速"), &on);
    if (on) {
        ImGui::SameLine();
        ImGui::SliderFloat(reinterpret_cast<const char*>(u8"速度"), &speed, 0.0F, 20.0F, "%.1f");
    }
}

auto HighSpeed::Update() -> void {
    const auto players = PlayerList::GetPlayers();
    for (const auto player : players) {
        try {
            SetPlayerSpeed(player, on ? speed : 1.5);
        }
        catch (...) {}
    }
}

auto HighSpeed::DrawStatus() -> void {}

auto HighSpeed::Save(nlohmann::json& json) -> void {
    json["playerSpeed"] = on;
    json["playerSpeedV"] = speed;
}

auto HighSpeed::Load(nlohmann::json& json) -> void {
    if (json.contains("playerSpeed")) {
        on = json["playerSpeed"];
    }
    if (json.contains("playerSpeedV")) {
        speed = json["playerSpeedV"];
    }
}