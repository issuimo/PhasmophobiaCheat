#include "ESP.h"
#include "GhostList.h"

#include "../library/d3d11hook.h"
#include "../library/magic_enum/magic_enum.hpp"

ESP::ESP() : Feature{} {
   
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
    ImGui::Checkbox(reinterpret_cast<const char*>(u8"鬼魂透视"), &ghostEsp);
}

auto ESP::Update() -> void {
    
}

auto ESP::DrawStatus() -> void {
    try {
        if (ghostEsp) {
            const auto ghosts = GhostList::GetGhosts();
            for (auto& ghost : ghosts) {
                const auto offset1 = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint64_t>(ghost) + 0x60);
                if (offset1 != 0) {
                    const auto offset2 = *reinterpret_cast<unity::CSharper::IL2cpp::Transform**>(offset1 + 0x60);
                    if (offset2 != nullptr) {
                        auto vector3 = unity::CSharper::IL2cpp::Camera::GetMain()->WorldToScreenPoint(offset2->GetPosition(), unity::CSharper::IL2cpp::Camera::m_eCameraEye_Center);
                        tagRECT Rect;
                        GetClientRect(dxhook::Hk11::GetHwnd(), &Rect);
                        float w = Rect.right - Rect.left;
                        float h = Rect.bottom - Rect.top;
                        vector3.y = h - vector3.y;
                        if ((vector3.x > 0 && vector3.y > 0) && (vector3.x < w && vector3.y < h) && vector3.z > 0) {
                            const auto offset1 = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint64_t>(ghost) + 0x38);
                            const auto type = *reinterpret_cast<GhostList::GhostType*>(offset1 + 0x28);
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(vector3.x, vector3.y), 0xFF0000FF, std::format("{}.{}\n[{}] M", *reinterpret_cast<int*>(offset1 + 0x28), magic_enum::enum_name<GhostList::GhostType>(type), vector3.z).c_str());
                        }
                    }
                }
            }
        }
    } catch (...) {}
}

auto ESP::Save(nlohmann::json& json) -> void {
    json["ghostEsp"] = ghostEsp;
}

auto ESP::Load(nlohmann::json& json) -> void {
    if (json.find("ghostEsp") != json.end()) {
        ghostEsp = json["ghostEsp"];
    }
}
