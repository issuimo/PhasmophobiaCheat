#include "PlayerList.h"
#include "NoDead.h"
#include "GhostList.h"
#include "DoorList.h"

auto PlayerList::Player_Awake_NEW(PlayerAPI* player) -> void {
    std::lock_guard lock(mutex);
    players.push_back(player);
    return HookManager::call(Player_Awake_NEW, player);
}

auto PlayerList::Player_OnDestroy_NEW(PlayerAPI* player) -> void {
    std::lock_guard lock(mutex);
    const auto      it = std::ranges::find(players, player);
    if (it != players.end())
        players.erase(it);
    GhostList::ClearVector();
    DoorList::ClearVector();
    return HookManager::call(Player_OnDestroy_NEW, player);
}

PlayerList::PlayerList() : Feature{} {
    HookManager::install(reinterpret_cast<void(*)(PlayerAPI*)>(
                             unity::Il2cpp::Method::GetAddress("Player", "Awake", 0)),
                         Player_Awake_NEW);
    HookManager::install(reinterpret_cast<void(*)(PlayerAPI*)>(
                             unity::Il2cpp::Method::GetAddress("Player", "OnDestroy", 0)),
                         Player_OnDestroy_NEW);
    StartKillingPlayer = reinterpret_cast<void(*)(void*)>(
        unity::Il2cpp::Method::GetAddress("Player", "StartKillingPlayer", 0));
}

auto PlayerList::GetInstance() -> PlayerList& {
    static PlayerList Instance;
    return Instance;
}

auto PlayerList::GetInfo() const -> const GuiInfo& {
    static GuiInfo info{reinterpret_cast<const char*>(u8"玩家"), reinterpret_cast<const char*>(u8"玩家列表"), true};
    return info;
}

auto PlayerList::Render() -> void {
    if (ImGui::BeginTable("PlayerList",
                          5,
                          ImGuiTableFlags_ScrollX | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollY |
                          ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
                          ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable,
                          ImVec2(0.0F, ImGui::GetTextLineHeightWithSpacing() * 8))) {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"名称"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"房间"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"死亡"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"地址"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"操作"), ImGuiTableColumnFlags_None);
        ImGui::TableHeadersRow();
        
        std::lock_guard lock(mutex);
        for (const auto& actor : players) {
            ImGui::TableNextRow();

            ImGui::PushID(actor);
            try {
                if (ImGui::TableSetColumnIndex(0)) {
                    try {
                        ImGui::Text(actor->GetName().c_str());
                    } catch (...) { }
                }
                if (ImGui::TableSetColumnIndex(1)) {
                    try {
                        ImGui::Text(actor->GetRoom()->GetName().c_str());
                    } catch (...) {}
                }
                if (ImGui::TableSetColumnIndex(2)) {
                    try {
                        ImGui::Text(std::format("{}", actor->GetDead()).c_str());
                    } catch (...) {}
                }
                if (ImGui::TableSetColumnIndex(3)) {
                    ImGui::Text(std::format("{:#x}", reinterpret_cast<std::uint64_t>(actor)).c_str());
                }
                if (ImGui::TableSetColumnIndex(4)) {
                    if (ImGui::SmallButton("kill")) {
                        StartKillingPlayer(actor);
                    }
                }
            } catch (...) {}
            ImGui::PopID();
        }

        ImGui::EndTable();
    }
}

auto PlayerList::Update() -> void {}

auto PlayerList::DrawStatus() -> void {}

auto PlayerList::Save(nlohmann::json& json) -> void {}

auto PlayerList::Load(nlohmann::json& json) -> void {}
