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

    enum GhostType {
        Spirit = 1,
        Wraith,
        Phantom,
        Poltergeist,
        Banshee,
        Jinn,
        Mare,
        Revenant,
        Shade,
        Demon,
        Yurei,
        Oni,
        Yokai,
        Hantu,
        Goryo,
        Myling,
        Onryo,
        TheTwins,
        Raiju,
        Obake,
        Mimic,
        Moroi,
        Deogen,
        Thaye
    };

    static auto GetGhosts() {
        return ghosts;
    }

    static auto ClearVector() {
        ghosts.clear();
    }

    inline static std::uintptr_t ghostStateOffset{ 0x28 };
    inline static std::uintptr_t ghostInfoOffset{ 0x38 };
    inline static std::uintptr_t levelRoomOffset{ 0x70 };
    inline static std::uintptr_t levelRoomNameOffset{ 0x68 };
protected:
    static auto Ghost_Awake_NEW(void* class_) -> void;
    GhostList();
    void* (*StartHuntingTimer)(void*);
private:
    inline static std::mutex         mutex;
    inline static std::vector<void*> ghosts;
};
