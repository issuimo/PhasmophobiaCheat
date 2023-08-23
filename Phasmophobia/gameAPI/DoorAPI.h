#pragma once
#include "../library/UnityHack.h"
class DoorAPI {
public:
    inline static void(*LockDoor)(DoorAPI*, bool);
    inline static void(*UnlockDoor)(DoorAPI*);
    inline static void(*OpenDoor)(DoorAPI*, float, bool, bool);

    void Lock(bool v) {
        LockDoor(this, v);
    }

    void UnLock() {
        UnlockDoor(this);
    }

    void Open(float v, bool v2, bool v3) {
        OpenDoor(this, v, v2, v3);
    }

    unity::CSharper::IL2cpp::GameObject* GetGameObject() {
        return *reinterpret_cast<unity::CSharper::IL2cpp::GameObject**>(reinterpret_cast<std::uint64_t>(this) + 0x100);
    }
};
