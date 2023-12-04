#pragma once
#ifndef PLAYERS_NODEAD
#define PLAYERS_NODEAD
#include "../../../Init.h"
#include "../Player.hpp"

class PlayerNoDead : init_space::Feature {
public:
	PlayerNoDead();
	~PlayerNoDead() = default;
	[[nodiscard]] auto GetInfo() const -> const GuiInfo & override;
	auto               Draw() -> void override;
	auto               Render() -> void override;
	auto               Update() -> void override;
	auto               Save(nlohmann::json& json) -> void override;
	auto               Load(nlohmann::json& json) -> void override;

	static auto GetInstance() -> PlayerNoDead*;
private:
	inline static bool noDead;

	inline static auto UNITY_CALLING_CONVENTION HDead(Player* player, bool arg, void* p) -> void;
	inline static auto UNITY_CALLING_CONVENTION HKillPlayer(Player* player, bool arg) -> void;
	inline static auto UNITY_CALLING_CONVENTION HStartKillingPlayer(Player* player) -> void;

};
#endif
