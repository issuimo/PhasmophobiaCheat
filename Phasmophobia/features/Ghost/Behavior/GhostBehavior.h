#pragma once
#ifndef GHOST_BEHAVIOR
#define GHOST_BEHAVIOR

#include "../../../Init.h"
#include "../Ghost.hpp"

class GhostBehavior : public  init_space::Feature {
public:
	GhostBehavior();
	~GhostBehavior() = default;
	[[nodiscard]] auto GetInfo() const -> const GuiInfo & override;
	auto               Draw() -> void override;
	auto               Render() -> void override;
	auto               Update() -> void override;
	auto               Save(nlohmann::json& json) -> void override;
	auto               Load(nlohmann::json& json) -> void override;

	static auto GetInstance() -> GhostBehavior*;
private:
	inline static bool noHunt;

	inline static auto UNITY_CALLING_CONVENTION HHunting(GhostAI* ghost_ai, bool arg, int i, PhotonMessageInfo* photon_message_info) -> void;
};

#endif
