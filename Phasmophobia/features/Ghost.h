#pragma once
#include "../Init.h"

class Ghost final : public init_space::Feature {
public:
    static auto GetInstance() -> Ghost&;
    auto        GetInfo() const -> const GuiInfo & override;
    auto        Render() -> void override;
    auto        Update() -> void override;
    auto        DrawStatus() -> void override;
    auto        Save(nlohmann::json& json) -> void override;
    auto        Load(nlohmann::json& json) -> void override;

protected:
    static auto Ghost_Hunting_NEW(void* p, bool arg, int i, void* p1) -> void;
    static auto Ghost_ChangeFavouriteRoomTo_NEW(void* p, void* arg) -> void;
    static auto Ghost_HuntingCloseDoor_NEW(void* p) -> void;
    static auto Ghost_HuntingCloseDoorNetworked_NEW(void* p, void* p1) -> void;
    Ghost();
private:
    inline static bool noHunt, noCloseDoor, noNewRoom, fixSpeed;
    inline static float speed;
};
