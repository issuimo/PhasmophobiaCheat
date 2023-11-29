#include "RoomList.h"

#include "Ghost.h"
#include "GhostList.h"
#include "PlayerList.h"

auto RoomList::LevelRoom_Awake_NEW(LevelAPI* levelApi) -> void {
    std::lock_guard lock(mutex);
    rooms.push_back(levelApi);
    return HookManager::Call(LevelRoom_Awake_NEW, levelApi);
}

RoomList::RoomList() : Feature{} {
    HookManager::Install(reinterpret_cast<void(*)(LevelAPI*)>(
        unity::Il2cpp::Method::GetAddress("LevelRoom", "Awake", 0)),
        LevelRoom_Awake_NEW);
}

auto RoomList::GetInstance() -> RoomList& {
    static RoomList Instance;
    return Instance;
}

auto RoomList::GetInfo() const -> const GuiInfo& {
    static GuiInfo info{ reinterpret_cast<const char*>(u8"房间"), reinterpret_cast<const char*>(u8"房间列表"), true };
    return info;
}

auto RoomList::Render() -> void {
    if (ImGui::BeginTable("RoomList",
        5,
        ImGuiTableFlags_ScrollX | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollY |
        ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
        ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable,
        ImVec2(0.0F, ImGui::GetTextLineHeightWithSpacing() * 8))) {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"名称"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"鬼房"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"地址"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"操作"), ImGuiTableColumnFlags_None);
        ImGui::TableHeadersRow();

        std::lock_guard lock(mutex);
        for (const auto& actor : rooms) {
            ImGui::TableNextRow();

            ImGui::PushID(actor);
            try {
                if (ImGui::TableSetColumnIndex(0)) {
                    try {
                        ImGui::Text(actor->GetName().c_str());
                    }
                    catch (...) {}
                }
                if (ImGui::TableSetColumnIndex(1)) {
                    try {
                        ImGui::Text(std::format("{}", (GhostList::GetGhosts()[0]->GetRoom()->GetName() == actor->GetName())).c_str());
                    }
                    catch (...) {}
                }
                if (ImGui::TableSetColumnIndex(2)) {
                    try {
                        ImGui::Text(std::format("{:#x}", reinterpret_cast<std::uint64_t>(actor)).c_str());
                    }
                    catch (...) {}
                }
                if (ImGui::TableSetColumnIndex(3)) {
                    try {
                        if (ImGui::SmallButton(reinterpret_cast<const char*>(u8"传送1号"))) {
                            PlayerList::GetPlayers()[0]->Teleport(reinterpret_cast<unity::CSharper::IL2cpp::Component*>(actor)->GetTransform()->GetPosition());
                        }
                        ImGui::SameLine();
                        if (ImGui::SmallButton(reinterpret_cast<const char*>(u8"传送2号"))) {
                            PlayerList::GetPlayers()[1]->Teleport(reinterpret_cast<unity::CSharper::IL2cpp::Component*>(actor)->GetTransform()->GetPosition());
                        }
                        ImGui::SameLine();
                        if (ImGui::SmallButton(reinterpret_cast<const char*>(u8"传送3号"))) {
                            PlayerList::GetPlayers()[2]->Teleport(reinterpret_cast<unity::CSharper::IL2cpp::Component*>(actor)->GetTransform()->GetPosition());
                        }
                        ImGui::SameLine();
                        if (ImGui::SmallButton(reinterpret_cast<const char*>(u8"传送4号"))) {
                            PlayerList::GetPlayers()[4]->Teleport(reinterpret_cast<unity::CSharper::IL2cpp::Component*>(actor)->GetTransform()->GetPosition());
                        }
                        ImGui::SameLine();
                        if (ImGui::SmallButton(reinterpret_cast<const char*>(u8"传送全部"))) {
                            auto players = PlayerList::GetPlayers();
                            for (const auto& player : players) {
                                player->Teleport(reinterpret_cast<unity::CSharper::IL2cpp::Component*>(actor)->GetTransform()->GetPosition());
                            }
                        }
                    }
                    catch (...) {}
                }
            }
            catch (...) {}
            ImGui::PopID();
        }

        ImGui::EndTable();
    }
}

auto RoomList::Update() -> void {}

auto RoomList::DrawStatus() -> void {}

auto RoomList::Save(nlohmann::json& json) -> void {}

auto RoomList::Load(nlohmann::json& json) -> void {}