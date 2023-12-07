#include "NoDead.hpp"

auto UNITY_CALLING_CONVENTION PlayerNoDead::HDead(Player* player, const bool arg, void* p) -> void {
	if (noDead)
		return;
	H::Fcall(HDead, player, arg, p);
}

auto UNITY_CALLING_CONVENTION PlayerNoDead::HKillPlayer(Player* player, const bool arg) -> void {
	if (noDead)
		return;
	H::Fcall(HKillPlayer, player, arg);
}

auto UNITY_CALLING_CONVENTION PlayerNoDead::HStartKillingPlayer(Player* player) -> void {
	if (noDead)
		return;
	H::Fcall(HStartKillingPlayer, player);
}

PlayerNoDead::PlayerNoDead() {
	if (Player::mDead && Player::mKillPlayer&& Player::mStartKillingPlayer) {
		H::Install(Player::mDead, HDead);
		H::Install(Player::mKillPlayer, HKillPlayer);
		H::Install(Player::mStartKillingPlayer, HStartKillingPlayer);
	}
}

auto PlayerNoDead::GetInfo() const -> const GuiInfo& {
	return *new GuiInfo{ reinterpret_cast<const char*>(u8"玩家 (Players)"), reinterpret_cast<const char*>(u8"属性 (Stats)"), true, false, false };
}
auto PlayerNoDead::Draw() -> void { Feature::Draw(); }
auto PlayerNoDead::Render() -> void {
	ImGui::Checkbox(reinterpret_cast<const char*>(u8"无敌 (invincibility)"), &noDead);
}
auto PlayerNoDead::Update() -> void { Feature::Update(); }
auto PlayerNoDead::Save(nlohmann::json& json) -> void {
	json["noDead"] = noDead;
}
auto PlayerNoDead::Load(nlohmann::json& json) -> void {
	if (json.contains("noDead")) {
		noDead = json["noDead"];
	}
}
auto PlayerNoDead::GetInstance() -> PlayerNoDead* {
	static PlayerNoDead player_no_dead;
	return &player_no_dead;
}
