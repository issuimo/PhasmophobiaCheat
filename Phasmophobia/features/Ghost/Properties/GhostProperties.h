#pragma once
#ifndef GHOST_PROPERTIES
#define GHOST_PROPERTIES

#include "../Ghost.hpp"
#include "../../../Init.h"

class GhostProperties : public  init_space::Feature {
public:
	GhostProperties() = default;
	~GhostProperties() = default;
	[[nodiscard]] auto GetInfo() const -> const GuiInfo & override;
	auto               Draw() -> void override;
	auto               Render() -> void override;
	auto               Update() -> void override;
	auto               Save(nlohmann::json& json) -> void override;
	auto               Load(nlohmann::json& json) -> void override;

	static auto GetInstance() -> GhostProperties*;
private:
	bool gSpeedEnable{};
	float gSpeed{};
};

#endif
