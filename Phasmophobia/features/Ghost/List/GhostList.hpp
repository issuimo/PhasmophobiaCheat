#pragma once
#ifndef GHOST_LIST
#define GHOST_LIST
#include "../../../Init.h"

class GhostList : init_space::Feature {
public:
	GhostList() = default;
	~GhostList() = default;
	[[nodiscard]] auto GetInfo() const -> const GuiInfo & override;
	auto               Draw() -> void override;
	auto               Render() -> void override;
	auto               Update() -> void override;
	auto               Save(nlohmann::json& json) -> void override;
	auto               Load(nlohmann::json& json) -> void override;

	static auto GetInstance() -> GhostList*;
private:

};
#endif
