#include "PlayerProperties.h"

auto PlayerProperties::GetInfo() const -> const GuiInfo& {
	return *new GuiInfo{ reinterpret_cast<const char*>(u8"玩家 (Players)"), reinterpret_cast<const char*>(u8"属性 (Properties)"), true, false, false };
}
auto PlayerProperties::Draw() -> void { Feature::Draw(); }
auto PlayerProperties::Render() -> void {
	std::lock_guard lock(Player::playersMutex);
	if (Player::players.empty()) {
		ImGui::Text(U8(u8"当前不存在任何玩家 (There are currently no players present.)"));
		return;
	}
	for (const auto& player : Player::players) {
		try {
			if (player->photonView && player->photonView->ptr && player->photonView->ptr->name && player->levelRoom && player->levelRoom->name) {
				if (ImGui::BeginTabBar("PlayersList")) {
					if (ImGui::BeginTabItem(player->photonView->ptr->name->ToString().c_str())) {
						
						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}
			}
		}
		catch (...) {}
	}
}
auto PlayerProperties::Update() -> void {
	
}
auto PlayerProperties::Save(nlohmann::json& json) -> void { Feature::Save(json); }
auto PlayerProperties::Load(nlohmann::json& json) -> void { Feature::Load(json); }
auto PlayerProperties::GetInstance() -> PlayerProperties* {
	static PlayerProperties playerProperties;
	return &playerProperties;
}
