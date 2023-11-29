#include "DoorList.h"

auto DoorList::Door_Awake_NEW(DoorAPI* doorApi) -> void {
    std::lock_guard lock(mutex);
    doors.push_back(doorApi);
    return HookManager::Call(Door_Awake_NEW, doorApi);
}

DoorList::DoorList() : Feature{} {
    HookManager::Install(reinterpret_cast<void(*)(DoorAPI*)>(unity::Il2cpp::Method::GetAddress("Door", "Awake", 0)), Door_Awake_NEW);
    DoorAPI::LockDoor = reinterpret_cast<void(*)(DoorAPI*, bool)>(unity::Il2cpp::Method::GetAddress("Door", "LockDoor", 1));
    DoorAPI::UnlockDoor = reinterpret_cast<void(*)(DoorAPI*)>(unity::Il2cpp::Method::GetAddress("Door", "UnlockDoor", 0));
    DoorAPI::OpenDoor = reinterpret_cast<void(*)(DoorAPI*, float, bool, bool)>(unity::Il2cpp::Method::GetAddress("Door", "OpenDoor", 3));
}

auto DoorList::GetInstance() -> DoorList& {
    static DoorList Instance;
    return Instance;
}

auto DoorList::GetInfo() const -> const GuiInfo& {
    static GuiInfo info{ reinterpret_cast<const char*>(u8"门"), reinterpret_cast<const char*>(u8"门列表"), true };
    return info;
}

auto DoorList::Render() -> void {
    std::lock_guard lock(mutex);
    
    if (ImGui::Button(reinterpret_cast<const char*>(u8"全上锁"))) {
        for (const auto& actor : doors) {
            actor->Lock(true);
        }
    }

    ImGui::SameLine();

    if (ImGui::Button(reinterpret_cast<const char*>(u8"全解锁"))) {
        for (const auto& actor : doors) {
            actor->UnLock();
        }
    }

    ImGui::SameLine();

    if (ImGui::Button(reinterpret_cast<const char*>(u8"全开门"))) {
        for (const auto& actor : doors) {
            actor->Open(45.0F, true, true);
        }
    }

    ImGui::SameLine();

    if (ImGui::Button(reinterpret_cast<const char*>(u8"全关门"))) {
        for (const auto& actor : doors) {
            actor->Open(0.0F, true, true);
        }
    }

    ImGui::SameLine();

    if (ImGui::Button(reinterpret_cast<const char*>(u8"删除门"))) {
        for (const auto& actor : doors) {
            unity::CSharper::IL2cpp::Object::DestroyImmediate(actor);
        }
        doors.clear();
    }
    if (ImGui::BeginTable("DoorList",
        2,
        ImGuiTableFlags_ScrollX | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollY |
        ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
        ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable,
        ImVec2(0.0F, ImGui::GetTextLineHeightWithSpacing() * 16))) {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"地址"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"操作"), ImGuiTableColumnFlags_None);
        ImGui::TableHeadersRow();
 
        for (const auto& actor : doors) {
            ImGui::TableNextRow();

            ImGui::PushID(actor);
            if (ImGui::TableSetColumnIndex(0)) {
                ImGui::Text(std::format("{:#x}", reinterpret_cast<std::uint64_t>(actor)).c_str());
            }
            if (ImGui::TableSetColumnIndex(1)) {
                if (ImGui::SmallButton(reinterpret_cast<const char*>(u8"上锁"))) {
                    try {
                        actor->Lock(true);
                    }
                    catch (...) {}
                }

                ImGui::SameLine();

                if (ImGui::SmallButton(reinterpret_cast<const char*>(u8"解锁"))) {
                    try {
                        actor->UnLock();
                    }
                    catch (...) {}
                }

                ImGui::SameLine();

                if (ImGui::SmallButton(reinterpret_cast<const char*>(u8"开门"))) {
                    try {
                        actor->Open(45.0F, true, true);
                    }
                    catch (...) {}
                }

                ImGui::SameLine();

                if (ImGui::SmallButton(reinterpret_cast<const char*>(u8"关门"))) {
                    try {
                        actor->Open(0.0F, true, true);
                    }
                    catch (...) {}
                }
            }

            ImGui::PopID();
        }

        ImGui::EndTable();
    }
}

auto DoorList::Update() -> void {}

auto DoorList::DrawStatus() -> void {}

auto DoorList::Save(nlohmann::json& json) -> void {}

auto DoorList::Load(nlohmann::json& json) -> void {}
