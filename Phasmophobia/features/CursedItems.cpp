#include "CursedItems.h"

auto CursedItems::MusicBox_BreakMusicBox_NEW(void* p, bool arg) -> void {
    if (musicBox) {
        return;
    }
    HookManager::Call(MusicBox_BreakMusicBox_NEW, p, arg);
}

auto CursedItems::MusicBox_TryBreakMusicBox_NEW(void* p, bool arg) -> void {
    if (musicBox) {
        return;
    }
    HookManager::Call(MusicBox_BreakMusicBox_NEW, p, arg);
}

auto CursedItems::HauntedMirror_BreakItem_NEW(void* p) -> void {
    if (hauntedMirror) {
        return;
    }
    HookManager::Call(HauntedMirror_BreakItem_NEW, p);
}

CursedItems::CursedItems() : Feature{} {
    HookManager::Install(reinterpret_cast<void(*)(void*, bool)>(unity::Il2cpp::Method::GetAddress("MusicBox", "BreakMusicBox", 1)), MusicBox_BreakMusicBox_NEW);
    HookManager::Install(reinterpret_cast<void(*)(void*, bool)>(unity::Il2cpp::Method::GetAddress("MusicBox", "TryBreakMusicBox", 1)), MusicBox_TryBreakMusicBox_NEW);
    HookManager::Install(reinterpret_cast<void(*)(void*)>(unity::Il2cpp::Method::GetAddress("HauntedMirror", "BreakItem", 0)), HauntedMirror_BreakItem_NEW);
}

auto CursedItems::GetInstance() -> CursedItems& {
    static CursedItems Instance;
    return Instance;
}

auto CursedItems::GetInfo() const -> const GuiInfo& {
    static GuiInfo info{ reinterpret_cast<const char*>(u8"诅咒道具"), reinterpret_cast<const char*>(u8"道具设置"), true };
    return info;
}

auto CursedItems::Render() -> void {
    ImGui::Checkbox(reinterpret_cast<const char*>(u8"音乐盒不碎"), &musicBox);
    ImGui::SameLine();
    ImGui::Checkbox(reinterpret_cast<const char*>(u8"闹鬼镜不碎"), &hauntedMirror);
}

auto CursedItems::Update() -> void { }

auto CursedItems::DrawStatus() -> void {}

auto CursedItems::Save(nlohmann::json& json) -> void {
    json["musicBox"] = musicBox;
    json["hauntedMirror"] = hauntedMirror;
}

auto CursedItems::Load(nlohmann::json& json) -> void {
    if (json.contains("musicBox")) {
        musicBox = json["musicBox"];
    }
    if (json.contains("hauntedMirror")) {
        hauntedMirror = json["hauntedMirror"];
    }
}
