#pragma once
#include "../Init.h"

class GhostList final : public initSpace::Feature {
public:
    static auto GetInstance() -> GhostList&;
    auto        GetInfo() const -> const GuiInfo & override;
    auto        Render() -> void override;
    auto        Update() -> void override;
    auto        DrawStatus() -> void override;
    auto        Save(nlohmann::json& json) -> void override;
    auto        Load(nlohmann::json& json) -> void override;

    enum GhostState {
        idle,
        wander,
        hunting,
        favouriteRoom,
        light,
        door,
        throwing,
        fusebox,
        appear,
        doorKnock,
        windowKnock,
        carAlarm,
        flicker,
        cctv,
        randomEvent,
        GhostAbility,
        mannequin,
        teleportObject,
        interact,
        summoningCircle,
        musicBox,
        dots,
        salt
    };

    static auto GetGhosts() {
        return ghosts;
    }

    static auto ClearVector() {
        ghosts.clear();
    }
protected:
    static auto Ghost_Awake_NEW(void* class_) -> void;
    GhostList();
    void* (*StartHuntingTimer)(void*);
    std::uintptr_t ghostStateOffset{ 0x28 };
    std::uintptr_t ghostInfoOffset{ 0x38 };
    std::uintptr_t levelRoomOffset{ 0x70 };
    std::uintptr_t levelRoomNameOffset{ 0x68 };
private:
    inline static std::mutex         mutex;
    inline static std::vector<void*> ghosts;
};
