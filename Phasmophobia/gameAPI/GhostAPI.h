#pragma once
#include <string>

#include "LevelAPI.h"
#include "PlayerAPI.h"

#include "../library/UnityHack.h"

class GhostAPI {
public:
    enum class GhostState {
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

    enum class GhostType : int {
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

    static std::string GetName(PlayerAPI* player) {
        try {
            const auto offset1 = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint64_t>(player) + 0xD8);
            const auto offset2 = *reinterpret_cast<std::uint64_t*>(offset1 + 0x130);
            const auto offset3 = *reinterpret_cast<unity::CSharper::IL2cpp::String**>(offset2 + 0xE0);
            return offset3->ToString();
        } catch (...) {
            return "";
        }
    }

    LevelAPI* GetRoom() {
        try {
            const auto offset1 = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint64_t>(this) + ghostInfoOffset);
            return *reinterpret_cast<LevelAPI**>(offset1 + levelRoomOffset);
        } catch (...) {
            return nullptr;
        }
    }

    bool IsHunt() {
        try {
            return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + ghostHuntOffset);
        } catch (...) {
            return false;
        }
    }

    GhostState GetGhostState() {
        try {
            return *reinterpret_cast<GhostState*>(reinterpret_cast<std::uint64_t>(this) + ghostStateOffset);
        } catch (...) {
            return GhostState::idle;
        }
    }

    GhostType GetGhostType() {
        try {
            const auto offset1 = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint64_t>(this) + ghostInfoOffset);
            return offset1 ? static_cast<GhostType>(*reinterpret_cast<int*>(offset1 + ghostStateOffset) + 1) : GhostType::Spirit;
        } catch (...) {
            return GhostType::Spirit;
        }
    }

    float GetSpeed() {
        try {
            return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + ghostSpeedOffset);
        } catch (...) {
            return .0F;
        }
    }

    void SetSpeed(float speed) {
        try {
            *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + ghostSpeedOffset) = speed;
        }
        catch (...) { }
    }

    unity::CSharper::IL2cpp::Transform* GetTransform() {
        try {
            const auto offset1 = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint64_t>(this) + 0x60);
            return *reinterpret_cast<unity::CSharper::IL2cpp::Transform**>(offset1 + 0x60);
        } catch (...) {
            return nullptr;
        }
    }
private:
    inline static std::uintptr_t ghostStateOffset{ 0x28 };
    inline static std::uintptr_t ghostInfoOffset{ 0x38 };
    inline static std::uintptr_t levelRoomOffset{ 0x70 };
    inline static std::uintptr_t ghostHuntOffset{ 0xC4 };
    inline static std::uintptr_t ghostSpeedOffset{ 0xB8 };
};
