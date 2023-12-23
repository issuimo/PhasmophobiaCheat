#pragma once
#ifndef PLAYER_PROPERTIES
#define PLAYER_PROPERTIES

#include "../../../Init.h"
#include "../Player.hpp"

class PlayerProperties : public  init_space::Feature {
public:
	PlayerProperties() = default;
	~PlayerProperties() = default;
	[[nodiscard]] auto GetInfo() const -> const GuiInfo & override;
	auto               Draw() -> void override;
	auto               Render() -> void override;
	auto               Update() -> void override;
	auto               Save(nlohmann::json& json) -> void override;
	auto               Load(nlohmann::json& json) -> void override;

	static auto GetInstance() -> PlayerProperties*;
private:

};

#endif
