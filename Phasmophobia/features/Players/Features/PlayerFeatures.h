#pragma once
#ifndef PLAYER_FEATURES
#define PLAYER_FEATURES
#include "../Player.hpp"
#include "../../../Init.h"

class PlayerFeatures : init_space::Feature {
public:
	PlayerFeatures() = default;
	~PlayerFeatures() = default;
	[[nodiscard]] auto GetInfo() const -> const GuiInfo & override;
	auto               Draw() -> void override;
	auto               Render() -> void override;
	auto               Update() -> void override;
	auto               Save(nlohmann::json& json) -> void override;
	auto               Load(nlohmann::json& json) -> void override;

	static auto GetInstance() -> PlayerFeatures*;
private:

};
#endif
