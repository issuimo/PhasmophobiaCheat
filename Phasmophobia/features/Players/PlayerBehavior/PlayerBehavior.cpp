#include "PlayerBehavior.hpp"

auto UNITY_CALLING_CONVENTION PlayerBehavior::HDead(Player* player, const bool arg, void* p) -> void {
	if (noDead)
		return;
	H::Fcall(HDead, player, arg, p);
}

auto UNITY_CALLING_CONVENTION PlayerBehavior::HKillPlayer(Player* player, const bool arg) -> void {
	if (noDead)
		return;
	H::Fcall(HKillPlayer, player, arg);
}

auto UNITY_CALLING_CONVENTION PlayerBehavior::HStartKillingPlayer(Player* player) -> void {
	if (noDead)
		return;
	H::Fcall(HStartKillingPlayer, player);
}

PlayerBehavior::PlayerBehavior() {
	if (Player::mDead && Player::mKillPlayer&& Player::mStartKillingPlayer) {
		H::Install(Player::mDead, HDead);
		H::Install(Player::mKillPlayer, HKillPlayer);
		H::Install(Player::mStartKillingPlayer, HStartKillingPlayer);
	}
}

auto PlayerBehavior::GetInfo() const -> const GuiInfo& {
	return *new GuiInfo{ reinterpret_cast<const char*>(u8"玩家 (Players)"), reinterpret_cast<const char*>(u8"行为 (Behavior)"), true, false, false };
}
auto PlayerBehavior::Draw() -> void { Feature::Draw(); }
auto PlayerBehavior::Render() -> void {
	ImGui::Checkbox(reinterpret_cast<const char*>(u8"不死 (No dead)"), &noDead);
}
auto PlayerBehavior::Update() -> void { Feature::Update(); }
auto PlayerBehavior::Save(nlohmann::json& json) -> void {
	json["noDead"] = noDead;
}
auto PlayerBehavior::Load(nlohmann::json& json) -> void {
	if (json.contains("noDead")) {
		noDead = json["noDead"];
	}
}
auto PlayerBehavior::GetInstance() -> PlayerBehavior* {
	static PlayerBehavior player_no_dead;
	return &player_no_dead;
}
