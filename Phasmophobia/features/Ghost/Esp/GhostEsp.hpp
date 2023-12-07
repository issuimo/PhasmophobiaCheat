#pragma once
#ifndef GHOST_ESP
#define GHOST_ESP
#include "../../../Init.h"

class GhostEsp : init_space::Feature {
public:
	GhostEsp() = default;
	~GhostEsp() = default;
	[[nodiscard]] auto GetInfo() const -> const GuiInfo & override;
	auto               Draw() -> void override;
	auto               Render() -> void override;
	auto               Update() -> void override;
	auto               Save(nlohmann::json& json) -> void override;
	auto               Load(nlohmann::json& json) -> void override;

	static auto GetInstance() -> GhostEsp*;
private:
	inline static bool enable;

};
#endif
