#include "GhostList.h"
#include "../library/magic_enum/magic_enum_all.hpp"
#include "PlayerList.h"

auto GhostList::Ghost_Awake_NEW(void* class_) -> void {
    std::cout << "ghost address:" << std::hex << class_ << "\n";
    std::lock_guard lock(mutex);
    ghosts.push_back(class_);
    HookManager::call(Ghost_Awake_NEW, class_);
}

GhostList::GhostList() : Feature{} {
    HookManager::install(reinterpret_cast<void(*)(void*)>(
        unity::Il2cpp::Method::GetAddress("GhostAI", "Awake", 0)),
        Ghost_Awake_NEW);
    StartHuntingTimer = reinterpret_cast<void*(*)(void*)>(unity::Il2cpp::Method::GetAddress("GhostAI", "StartHuntingTimer", 0));
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
        ImVec2(0.0F, ImGui::GetTextLineHeightWithSpacing() * 8))) {
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
                    auto player = PlayerList::GetPlayers();
                    const auto offset1 = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint64_t>(player[0]) + 0xD8);
                    if (offset1 != 0) {
                        const auto offset2 = *reinterpret_cast<std::uint64_t*>(offset1 + 0x130);
                        if (offset2 != 0) {
                            const auto offset3 = *reinterpret_cast<std::uint64_t*>(offset2 + 0xE0);
                            if (offset3 != 0) {
                                ImGui::Text(std::format("{}", reinterpret_cast<unity::CSharper::IL2cpp::String*>(offset3)->ToString()).c_str());
                            }
                        }
                    }
                }
                if (ImGui::TableSetColumnIndex(1)) {
                    ImGui::Text(std::format("{:#x}", reinterpret_cast<std::uint64_t>(actor)).c_str());
                }
                if (ImGui::TableSetColumnIndex(2)) {
                    if (ImGui::SmallButton("Hunting")) {
                        StartHuntingTimer(actor);
                    }
                }
                if (ImGui::TableSetColumnIndex(3)) {
                    ImGui::Text(std::format("{}", magic_enum::enum_name<GhostState>(*reinterpret_cast<GhostState*>(reinterpret_cast<std::uint64_t>(actor) + ghostStateOffset))).c_str());
                }
                if (ImGui::TableSetColumnIndex(4)) {
                    const auto offset1 = reinterpret_cast<std::uint64_t>(actor) + ghostInfoOffset;
                    const auto offset2 = *reinterpret_cast<std::uint64_t*>(offset1) + levelRoomOffset;
                    const auto offset3 = *reinterpret_cast<std::uint64_t*>(offset2) + levelRoomNameOffset;
                    ImGui::Text(std::format("{}", reinterpret_cast<unity::CSharper::IL2cpp::String*>(*reinterpret_cast<std::uint64_t*>(offset3))->ToString()).c_str());
                }
                if (ImGui::TableSetColumnIndex(5)) {;
                    const auto offset1 = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint64_t>(actor) + 0x38);
                    const auto type = *reinterpret_cast<GhostType*>(offset1 + 0x28);
                    ImGui::Text(std::format("{}.{}", *reinterpret_cast<int*>(offset1 + 0x28), magic_enum::enum_name<GhostType>(type)).c_str());
                }
                if (ImGui::TableSetColumnIndex(6)) {
                    ImGui::Text(std::format("{}", *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(actor) + 0xC4)).c_str());
                }
                if (ImGui::TableSetColumnIndex(7)) {
                    ImGui::Text(std::format("{}", *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(actor) + 0xB8)).c_str());
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
