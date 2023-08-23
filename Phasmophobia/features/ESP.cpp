#include "ESP.h"

#include "DoorList.h"
#include "GhostList.h"

#include "../library/magic_enum/magic_enum.hpp"

auto ESP::MusicBox_ctor_NEW(void* p) -> void {
    CursedItemsControllerAPI::musicBox_ = reinterpret_cast<std::uintptr_t>(p);
    return HookManager::call(MusicBox_ctor_NEW, p);
}

auto ESP::VoodooDoll_ctor_NEW(void* p) -> void {
    CursedItemsControllerAPI::voodooDoll_ = reinterpret_cast<std::uintptr_t>(p);
    return HookManager::call(VoodooDoll_ctor_NEW, p);
}

auto ESP::MonkeyPaw_ctor_NEW(void* p) -> void {
    CursedItemsControllerAPI::monkeyPaw_ = reinterpret_cast<std::uintptr_t>(p);
    return HookManager::call(MonkeyPaw_ctor_NEW, p);
}

auto ESP::HauntedMirror_ctor_NEW(void* p) -> void {
    CursedItemsControllerAPI::hauntedMirror_ = reinterpret_cast<std::uintptr_t>(p);
    return HookManager::call(HauntedMirror_ctor_NEW, p);
}

auto ESP::OuijaBoard_ctor_NEW(void* p) -> void {
    CursedItemsControllerAPI::ouijaBoard_ = reinterpret_cast<std::uintptr_t>(p);
    return HookManager::call(OuijaBoard_ctor_NEW, p);
}

auto ESP::SummoningCircle_ctor_NEW(void* p) -> void {
    CursedItemsControllerAPI::summoningCircle_ = reinterpret_cast<std::uintptr_t>(p);
    return HookManager::call(SummoningCircle_ctor_NEW, p);
}

auto ESP::TarotCard_ctor_NEW(void* p) -> void {
    CursedItemsControllerAPI::tarotCards_ = reinterpret_cast<std::uintptr_t>(p);
    return HookManager::call(TarotCard_ctor_NEW, p);
}

ESP::ESP() : Feature{} {
    HookManager::install(reinterpret_cast<void(*)(void*)>(unity::Il2cpp::Method::GetAddress("MusicBox", ".ctor", 0)), MusicBox_ctor_NEW);
    HookManager::install(reinterpret_cast<void(*)(void*)>(unity::Il2cpp::Method::GetAddress("VoodooDoll", ".ctor", 0)), VoodooDoll_ctor_NEW);
    HookManager::install(reinterpret_cast<void(*)(void*)>(unity::Il2cpp::Method::GetAddress("MonkeyPaw", ".ctor", 0)), MonkeyPaw_ctor_NEW);
    HookManager::install(reinterpret_cast<void(*)(void*)>(unity::Il2cpp::Method::GetAddress("HauntedMirror", ".ctor", 0)), HauntedMirror_ctor_NEW);
    HookManager::install(reinterpret_cast<void(*)(void*)>(unity::Il2cpp::Method::GetAddress("OuijaBoard", ".ctor", 0)), OuijaBoard_ctor_NEW);
    HookManager::install(reinterpret_cast<void(*)(void*)>(unity::Il2cpp::Method::GetAddress("SummoningCircle", ".ctor", 0)), SummoningCircle_ctor_NEW);
    HookManager::install(reinterpret_cast<void(*)(void*)>(unity::Il2cpp::Method::GetAddress("TarotCard", ".ctor", 0)), TarotCard_ctor_NEW);
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

        if (curseObj) {
            if (CursedItemsControllerAPI::hasHauntedMirror()) {
                auto vector3 = camera->WorldToScreenPoint(static_cast<unity::CSharper::IL2cpp::Component*>(CursedItemsControllerAPI::hasHauntedMirror())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(148, 105, 204), std::format("HauntedMirror \n [{}] M", vector3.z).c_str());
                }
            }
            if (CursedItemsControllerAPI::hasMonkeyPaw()) {
                auto vector3 = camera->WorldToScreenPoint(static_cast<unity::CSharper::IL2cpp::Component*>(CursedItemsControllerAPI::hasMonkeyPaw())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(148, 105, 204), std::format("MonkeyPaw \n [{}] M", vector3.z).c_str());
                }
            }
            if (CursedItemsControllerAPI::hasMusicBox()) {
                auto vector3 = camera->WorldToScreenPoint(static_cast<unity::CSharper::IL2cpp::Component*>(CursedItemsControllerAPI::hasMusicBox())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(148, 105, 204), std::format("MusicBox \n [{}] M", vector3.z).c_str());
                }
            }
            if (CursedItemsControllerAPI::hasOuijaBoard()) {
                auto vector3 = camera->WorldToScreenPoint(static_cast<unity::CSharper::IL2cpp::Component*>(CursedItemsControllerAPI::hasOuijaBoard())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(148, 105, 204), std::format("OuijaBoard \n [{}] M", vector3.z).c_str());
                }
            }
            if (CursedItemsControllerAPI::hasSummoningCircle()) {
                auto vector3 = camera->WorldToScreenPoint(static_cast<unity::CSharper::IL2cpp::Component*>(CursedItemsControllerAPI::hasSummoningCircle())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(148, 105, 204), std::format("SummoningCircle \n [{}] M", vector3.z).c_str());
                }
            }
            if (CursedItemsControllerAPI::hasTarotCards()) {
                auto vector3 = camera->WorldToScreenPoint(static_cast<unity::CSharper::IL2cpp::Component*>(CursedItemsControllerAPI::hasTarotCards())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                vector3.y = initSpace::GuiInfo::h - vector3.y;
                if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < initSpace::GuiInfo::w && vector3.y < initSpace::GuiInfo::h) && vector3.z > 0) {
                    ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), ImColor(148, 105, 204), std::format("TarotCards \n [{}] M", vector3.z).c_str());
                }
            }
            if (CursedItemsControllerAPI::hasVoodooDoll()) {
                auto vector3 = camera->WorldToScreenPoint(static_cast<unity::CSharper::IL2cpp::Component*>(CursedItemsControllerAPI::hasVoodooDoll())->GetTransform()->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
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
