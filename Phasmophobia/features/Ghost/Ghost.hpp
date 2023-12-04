#pragma once
#ifndef GHOST
#define GHOST
#include "../../Init.h"

#include "../Rooms/Room.hpp"

#pragma pack(8)
class Ghost : public II::MonoBehaviour {
public:
    char space1[0x8];
    enum class GhostState : std::int64_t {
        Idle,
        Wander,
        Hunting,
        FavouriteRoom,
        Light,
        Door,
        Throwing,
        Fusebox,
        Appear,
        DoorKnock,
        WindowKnock,
        CarAlarm,
        Flicker,
        Cctv,
        RandomEvent,
        GhostAbility,
        Mannequin,
        TeleportObject,
        Interact,
        SummoningCircle,
        MusicBox,
        Dots,
        Salt
    }ghostState;
    char space2[0x8];
    enum class GhostType : std::int32_t {
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

    enum class Proof : std::int32_t {
        None,
        Emf,
        SpiritBox,
        UltraViolet,
        GhostOrb,
        GhostWritingBook,
        Temperature,
        DotsProjector
    };

    struct A : MonoBehaviour {
        char space1[0x8];
        GhostType ghostType;
        GhostType ghostType2;
        II::List<Proof>* proof;
        II::List<Proof>* proof2;
        char space2[0x30];
        Room* room;
    }*ghostInfo;
    char space3[0x78];
    float speed;
    char space4[0x8];
    bool hunt;

    static auto InitOnce() -> void;
	inline static Ghost* ghost{};
private:
    inline static IM::MethodPointer<void, Ghost*> mAwake{};
    inline static auto UNITY_CALLING_CONVENTION  HAwake(Ghost* _this) -> void;
};

#endif