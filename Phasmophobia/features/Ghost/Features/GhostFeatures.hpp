#pragma once
#ifndef GHOST_FEATURES
#define GHOST_FEATURES

#include "../../../Init.h"

class GhostFeatures : public  init_space::Feature{
public:
	GhostFeatures() = default;
	~GhostFeatures() = default;
	[[nodiscard]] auto GetInfo() const -> const GuiInfo & override;
	auto               Draw() -> void override;
	auto               Render() -> void override;
	auto               Update() -> void override;
	auto               Save(nlohmann::json& json) -> void override;
	auto               Load(nlohmann::json& json) -> void override;

	static auto GetInstance() -> GhostFeatures*;
private:
	inline static bool enable;
};

#endif
