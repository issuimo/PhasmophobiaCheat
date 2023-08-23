#include "ESP.h"

#include "DoorList.h"
#include "GhostList.h"

#include "../gameAPI/CursedItemsControllerAPI.h"

#include "../library/magic_enum/magic_enum.hpp"

auto ESP::CursedItemsController_Awake_NEW(void* p) -> void {
    CursedItemsController_This = reinterpret_cast<std::uintptr_t>(p);
    return HookManager::call(CursedItemsController_Awake_NEW, p);
}

ESP::ESP() : Feature{} {
    HookManager::install(reinterpret_cast<void(*)(void*)>(unity::Il2cpp::Method::GetAddress("CursedItemsController", "Awake", 0)), CursedItemsController_Awake_NEW);
}

auto ESP::GetInstance() -> ESP& {
    static ESP Instance;
    return Instance;
}

auto ESP::GetInfo() const -> const GuiInfo& {
    static GuiInfo info{ reinterpret_cast<const char*>(u8"透视"), reinterpret_cast<const char*>(u8"透视设置"), true };
    return info;
}

auto ESP::Render() -> void {
    ImGui::Checkbox(reinterpret_cast<const char*>(u8"鬼魂"), &ghostEsp);
    ImGui::SameLine();
    ImGui::Checkbox(reinterpret_cast<const char*>(u8"门"), &doorEsp);
    ImGui::SameLine();
    ImGui::Checkbox(reinterpret_cast<const char*>(u8"鬼房"), &gRoomEsp);
    ImGui::SameLine();
    ImGui::Checkbox(reinterpret_cast<const char*>(u8"诅咒道具"), &curseObj);
}

auto ESP::Update() -> void {
}

auto ESP::DrawStatus() -> void {
    try {
        const auto camera = unity::CSharper::IL2cpp::Camera::GetMain();

        if (ghostEsp) {
            const auto ghosts = GhostList::GetGhosts();
            for (auto& ghost : ghosts) {
                auto vector3 = camera->WorldToScreenPoint(reinterpret_cast<unity::CSharper::IL2cpp::Component*>(ghost)->GetTransform()->GetPosition(),unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(255, 0, 0), std::format("{}.{}\n[{}] M", static_cast<int>(ghost->GetGhostType()), magic_enum::enum_name<GhostAPI::GhostType>(ghost->GetGhostType()), vector3.z).c_str());
                }
            }
        }

        if (doorEsp) {
            const auto doors = DoorList::GetDoors();
            for (auto& door : doors) {
                auto vector3 = camera->WorldToScreenPoint(reinterpret_cast<unity::CSharper::IL2cpp::Component*>(door)->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(100, 240, 100), std::format("Door\n[{}] M", vector3.z).c_str());
                }
            }
        }

        if (gRoomEsp) {
            const auto ghosts = GhostList::GetGhosts();
            for (auto& ghost : ghosts) {
                auto vector3 = camera->WorldToScreenPoint(reinterpret_cast<unity::CSharper::IL2cpp::Component*>(ghost->GetRoom())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(199, 123, 154), std::format("GhostRoom:{} \n [{}] M", ghost->GetRoom()->GetName(), vector3.z).c_str());
                }
            }
        }

        if (curseObj && CursedItemsController_This) {
            const auto items = reinterpret_cast<CursedItemsControllerAPI*>(CursedItemsController_This);
            if (items->hasHauntedMirror()) {
                auto vector3 = camera->WorldToScreenPoint(static_cast<unity::CSharper::IL2cpp::Component*>(items->hasHauntedMirror())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(148, 105, 204), std::format("HauntedMirror \n [{}] M", vector3.z).c_str());
                }
            }
            if (items->hasMonkeyPaw()) {
                auto vector3 = camera->WorldToScreenPoint(static_cast<unity::CSharper::IL2cpp::Component*>(items->hasMonkeyPaw())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(148, 105, 204), std::format("MonkeyPaw \n [{}] M", vector3.z).c_str());
                }
            }
            if (items->hasMusicBox()) {
                auto vector3 = camera->WorldToScreenPoint(static_cast<unity::CSharper::IL2cpp::Component*>(items->hasMusicBox())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(148, 105, 204), std::format("MusicBox \n [{}] M", vector3.z).c_str());
                }
            }
            if (items->hasOuijaBoard()) {
                auto vector3 = camera->WorldToScreenPoint(static_cast<unity::CSharper::IL2cpp::Component*>(items->hasOuijaBoard())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(148, 105, 204), std::format("OuijaBoard \n [{}] M", vector3.z).c_str());
                }
            }
            if (items->hasSummoningCircle()) {
                auto vector3 = camera->WorldToScreenPoint(static_cast<unity::CSharper::IL2cpp::Component*>(items->hasSummoningCircle())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(148, 105, 204), std::format("SummoningCircle \n [{}] M", vector3.z).c_str());
                }
            }
            if (items->hasTarotCards()) {
                auto vector3 = camera->WorldToScreenPoint(static_cast<unity::CSharper::IL2cpp::Component*>(items->hasTarotCards())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(148, 105, 204), std::format("TarotCards \n [{}] M", vector3.z).c_str());
                }
            }
            if (items->hasVoodooDoll()) {
                auto vector3 = camera->WorldToScreenPoint(static_cast<unity::CSharper::IL2cpp::Component*>(items->hasVoodooDoll())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(148, 105, 204), std::format("VoodooDoll \n [{}] M", vector3.z).c_str());
                }
            }
        }
    } catch (...) {}
}

auto ESP::Save(nlohmann::json& json) -> void {
    json["ghostEsp"] = ghostEsp;
    json["doorEsp"] = doorEsp;
    json["gRoomEsp"] = gRoomEsp;
    json["curseObj"] = curseObj;
}

auto ESP::Load(nlohmann::json& json) -> void {
    if (json.contains("ghostEsp")) {
        ghostEsp = json["ghostEsp"];
    }
    if (json.contains("doorEsp")) {
        doorEsp = json["doorEsp"];
    }
    if (json.contains("gRoomEsp")) {
        gRoomEsp = json["gRoomEsp"];
    }
    if (json.contains("curseObj")) {
        curseObj = json["curseObj"];
    }
}
