#include "GhostBehavior.h"

auto UNITY_CALLING_CONVENTION GhostBehavior::HHunting(GhostAI* ghost_ai, const bool arg, const int i, PhotonMessageInfo* photon_message_info) -> void {
	if (noHunt) return;
	H::Fcall(HHunting, ghost_ai, arg, i, photon_message_info);
}

GhostBehavior::GhostBehavior() {
	if (GhostAI::mHunting) {
		H::Install(GhostAI::mHunting, HHunting);
	}
}
auto GhostBehavior::GetInfo() const -> const GuiInfo& { return *new GuiInfo{ reinterpret_cast<const char*>(u8"鬼魂 (Ghost)"), reinterpret_cast<const char*>(u8"行为 (Behavior)"), true, false, false }; }
auto GhostBehavior::Draw() -> void { Feature::Draw(); }
auto GhostBehavior::Render() -> void {
	ImGui::Checkbox(U8(u8"不猎杀 (No hunt)"), &noHunt);
}
auto GhostBehavior::Update() -> void { Feature::Update(); }
auto GhostBehavior::Save(nlohmann::json& json) -> void { Feature::Save(json); }
auto GhostBehavior::Load(nlohmann::json& json) -> void { Feature::Load(json); }
auto GhostBehavior::GetInstance() -> GhostBehavior* {
	static GhostBehavior ghost_behavior;
	return &ghost_behavior;
}
