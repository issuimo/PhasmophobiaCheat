#pragma once
#include "../Init.h"

class MoreXP final : public initSpace::Feature {
public:
    static auto GetInstance() -> MoreXP&;
    auto        GetInfo() const -> const GuiInfo & override;
    auto        Render() -> void override;
    auto        Update() -> void override;
    auto        DrawStatus() -> void override;
    auto        Save(nlohmann::json& json) -> void override;
    auto        Load(nlohmann::json& json) -> void override;

protected:
    static auto LevelValues_IsPerfectGame_NEW(unity::Il2cpp::Class* class_) -> bool;
    static auto LevelValues_GetInestigationBonusReward_NEW(unity::Il2cpp::Class* class_) -> int;
    static auto LevelValues_CompletedMultiplierChallenge_NEW(unity::Il2cpp::Class* class_) -> bool;
    MoreXP();

private:
    inline static bool on{ false };
    inline static int value{ 0 };
};
