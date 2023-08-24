#pragma once
#include "../Init.h"

class NoDead final : public initSpace::Feature {
public:
    static auto GetInstance() -> NoDead&;
    auto        GetInfo() const -> const GuiInfo& override;
    auto        Render() -> void override;
    auto        Update() -> void override;
    auto        DrawStatus() -> void override;
    auto        Save(nlohmann::json& json) -> void override;
    auto        Load(nlohmann::json& json) -> void override;

    static auto Player_StartKillingPlayer_NEW(void* p) -> void;
    static auto Player_KillPlayer_NEW(void* p, bool v) -> void;
    static auto Player_Dead_NEW(void* p, bool arg, void* po) -> void;
    static auto Player_DeadRoomEffects_NEW(void* p) -> void;

    static void SetNoDead(bool v) {
        noDead = v;
    }

protected:
    NoDead();

private:
    inline static bool noDead;
};
