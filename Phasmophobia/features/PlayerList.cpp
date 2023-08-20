#include "PlayerList.h"
#include "NoDead.h"
#include "GhostList.h"

auto PlayerList::Player_Awake_NEW(unity::Il2cpp::Class* player) -> void {
    std::lock_guard lock(mutex);
    players.push_back(player);
    HookManager::call(Player_Awake_NEW, player);
}

auto PlayerList::Player_OnDestroy_NEW(unity::Il2cpp::Class* player) -> void {
    std::lock_guard lock(mutex);
    const auto      it = std::ranges::find(players, player);
    if (it != players.end())
        players.erase(it);
    GhostList::ClearVector();
}

PlayerList::PlayerList() : Feature{} {
    HookManager::install(reinterpret_cast<void(*)(unity::Il2cpp::Class*)>(
                             unity::Il2cpp::Method::GetAddress("Player", "Awake", 0)),
                         Player_Awake_NEW);
    HookManager::install(reinterpret_cast<void(*)(unity::Il2cpp::Class*)>(
                             unity::Il2cpp::Method::GetAddress("Player", "OnDestroy", 0)),
                         Player_OnDestroy_NEW);
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
                          2,
                          ImGuiTableFlags_ScrollX | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollY |
                          ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
                          ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable,
                          ImVec2(0.0F, ImGui::GetTextLineHeightWithSpacing() * 8))) {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"地址"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"操作"), ImGuiTableColumnFlags_None);
        ImGui::TableHeadersRow();

        std::lock_guard lock(mutex);
        for (const auto& actor : players) {
            ImGui::TableNextRow();

            ImGui::PushID(actor);
            try {
                if (ImGui::TableSetColumnIndex(0)) {
                    ImGui::Text(std::format("{:#x}", reinterpret_cast<std::uint64_t>(actor)).c_str());
                }
                if (ImGui::TableSetColumnIndex(1)) {
                    if (ImGui::SmallButton("kill")) {
                        try {
                            HookManager::call(NoDead::Player_StartKillingPlayer_NEW, actor);
                        } catch (...) {}
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
