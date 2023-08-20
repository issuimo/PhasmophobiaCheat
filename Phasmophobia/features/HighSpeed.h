#pragma once
#include "../Init.h"

class HighSpeed final : public initSpace::Feature {
public:
    static auto GetInstance() -> HighSpeed&;
    auto        GetInfo() const -> const GuiInfo & override;
    auto        Render() -> void override;
    auto        Update() -> void override;
    auto        DrawStatus() -> void override;
    auto        Save(nlohmann::json& json) -> void override;
    auto        Load(nlohmann::json& json) -> void override;

protected:
    HighSpeed();

    void(*SetPlayerSpeed)(void*, float);
private:
    inline static bool on{ false };
    inline static float speed{ 1.5F };
};
