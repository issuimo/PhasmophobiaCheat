#pragma once
#ifndef ROOMS_LIST
#define ROOMS_LIST
#include "../../../Init.h"

#include "../Room.hpp"

class RoomList : init_space::Feature {
public:
	RoomList() = default;
	~RoomList() = default;
	[[nodiscard]] auto GetInfo() const -> const GuiInfo & override;
	auto               Draw() -> void override;
	auto               Render() -> void override;
	auto               Update() -> void override;
	auto               Save(nlohmann::json& json) -> void override;
	auto               Load(nlohmann::json& json) -> void override;

	static auto GetInstance() -> RoomList*;
private:
	
};
#endif
