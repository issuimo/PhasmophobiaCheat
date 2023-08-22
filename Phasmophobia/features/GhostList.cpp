#include "GhostList.h"
#include "PlayerList.h"
#include "../library/magic_enum/magic_enum.hpp"

auto GhostList::Ghost_Awake_NEW(GhostAPI* class_) -> void {
    std::lock_guard lock(mutex);
    ghosts.push_back(class_);
    return HookManager::call(Ghost_Awake_NEW, class_);
}

GhostList::GhostList() : Feature{} {
    HookManager::install(reinterpret_cast<void(*)(GhostAPI*)>(unity::Il2cpp::Method::GetAddress("GhostAI", "Awake", 0)),Ghost_Awake_NEW);
    GhostAPI::Interact_Address = reinterpret_cast<void(*)(void*)>(unity::Il2cpp::Method::GetAddress("GhostAI", "StartHuntingTimer", 0));
}

auto GhostList::GetInstance() -> GhostList& {
    static GhostList Instance;
    return Instance;
}

auto GhostList::GetInfo() const -> const GuiInfo& {
    static GuiInfo info{ reinterpret_cast<const char*>(u8"鬼魂"), reinterpret_cast<const char*>(u8"鬼魂列表"), true };
    return info;
}

auto GhostList::Render() -> void {
    if (ImGui::BeginTable("GhostList",
        8,
        ImGuiTableFlags_ScrollX | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollY |
        ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
        ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable,
        ImVec2(0.0F, ImGui::GetTextLineHeightWithSpacing() * 4))) {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"名称"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"地址"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"操作"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"状态"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"鬼房"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"类型"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"猎杀"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"速度"), ImGuiTableColumnFlags_None);
        ImGui::TableHeadersRow();

        std::lock_guard lock(mutex);
        for (const auto& actor : ghosts) {
            ImGui::TableNextRow();
            ImGui::PushID(actor);
            try {
                if (ImGui::TableSetColumnIndex(0)) {
                    try {
                        auto player = PlayerList::GetPlayers();
                        if (!player.empty()) {
                            ImGui::Text(GhostAPI::GetName(player[0]).c_str());
                        }
                    } catch (...) {}
                }
                if (ImGui::TableSetColumnIndex(1)) {
                    ImGui::Text(std::format("{:#x}", reinterpret_cast<std::uint64_t>(actor)).c_str());
                }
                if (ImGui::TableSetColumnIndex(2)) {
                    if (ImGui::SmallButton(reinterpret_cast<const char*>(u8"互动"))) {
                        try {
                            actor->Interact();
                        }catch (...) { }
                    }
                }
                if (ImGui::TableSetColumnIndex(3)) {
                    try {
                        ImGui::Text(std::format("{}", magic_enum::enum_name<GhostAPI::GhostState>(actor->GetGhostState())).c_str());
                    } catch (...) {}
                }
                if (ImGui::TableSetColumnIndex(4)) {
                    try {
                        ImGui::Text(actor->GetRoom()->GetName().c_str());
                    } catch (...) {}
                }
                if (ImGui::TableSetColumnIndex(5)) {;
                    try {
                        ImGui::Text(std::format("{}.{}",static_cast<int>(actor->GetGhostType()), magic_enum::enum_name<GhostAPI::GhostType>(actor->GetGhostType())).c_str());
                    } catch (...) {}
                }
                if (ImGui::TableSetColumnIndex(6)) {
                    try {
                        ImGui::Text(std::format("{}", actor->IsHunt()).c_str());
                    } catch (...) {}
                }
                if (ImGui::TableSetColumnIndex(7)) {
                    try {
                        ImGui::Text(std::format("{}", actor->GetSpeed()).c_str());
                    } catch (...) {}
                }
            }
            catch (...) {}
            ImGui::PopID();
        }

        ImGui::EndTable();
    }
}

auto GhostList::Update() -> void {}

auto GhostList::DrawStatus() -> void {}

auto GhostList::Save(nlohmann::json& json) -> void {}

auto GhostList::Load(nlohmann::json& json) -> void {}
