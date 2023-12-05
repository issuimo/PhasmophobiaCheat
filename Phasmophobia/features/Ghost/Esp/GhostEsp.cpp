#include "GhostEsp.hpp"
#include "../Ghost.hpp"

auto GhostEsp::GetInfo() const -> const GuiInfo& { return *new GuiInfo{ reinterpret_cast<const char*>(u8"鬼魂 (Ghost)"), reinterpret_cast<const char*>(u8"透视 (Esp)"), true, false, true }; }
auto GhostEsp::Draw() -> void {
	if (enable && Ghost::ghost) {
		try {
			auto i = 0;
			for (const auto pCollider : Ghost::ghost->GetGameObject()->GetComponentsInChildren<II::Renderer*>(I::Get("UnityEngine.CoreModule.dll")->Get("Renderer"))) {
				if (i == 2 || i == 8) auto ract = drawMath::DrawBox(pCollider, ImColor{ 255, 0, 0 });
				i++;
			}
			if (auto point = II::Camera::GetMain()->WorldToScreenPoint(Ghost::ghost->GetTransform()->GetPosition(), UnityResolve::UnityType::Camera::Eye::Mono); point.z > 0) {
				point.y = init_space::Info::h - point.y;
				DrawTextWithOutline(ImGui::GetBackgroundDrawList(), { point.x, point.y }, std::format("[{}] {}.{}", Ghost::ghost->ghostState, static_cast<int>(Ghost::ghost->ghostInfo->ghostType), Ghost::ghost->ghostInfo->ghostType).c_str(), ImColor(255, 0, 0), 1.0f, ImGuiEx::OutlineSide::All, ImColor(0, 0, 0));
			}
		} catch (...) {}
	}
}

auto GhostEsp::Render() -> void {
	ImGui::Checkbox(U8(u8"启用(Enable)"), &enable);
}
auto GhostEsp::Update() -> void { Feature::Update(); }
auto GhostEsp::Save(nlohmann::json& json) -> void {
	
}
auto GhostEsp::Load(nlohmann::json& json) -> void {

}
auto GhostEsp::GetInstance() -> GhostEsp* {
	static GhostEsp ghost_esp;
	return &ghost_esp;
}
