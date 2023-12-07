#pragma once
#ifndef PLAYERS_LIST
#define PLAYERS_LIST
#include "../../../Init.h"
#include "../Player.hpp"

class PlayerList : init_space::Feature {
public:
	PlayerList();
	~PlayerList() = default;
	[[nodiscard]] auto GetInfo() const -> const GuiInfo& override;
	auto               Draw() -> void override;
	auto               Render() -> void override;
	auto               Update() -> void override;
	auto               Save(nlohmann::json& json) -> void override;
	auto               Load(nlohmann::json& json) -> void override;

	static auto GetInstance() -> PlayerList*;
private:
	
};
#endif
