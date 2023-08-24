#pragma once

#include <string>
#include "LevelAPI.h"
#include "../library/UnityHack.h"

class PlayerAPI {
public:
    inline static void(*Tel)(void*, unity::CSharper::Vector3);

    std::string GetName() {
        try {
            const auto offset1 = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint64_t>(this) + 0x20);
            const auto offset2 = *reinterpret_cast<std::uint64_t*>(offset1 + 0x70);
            const auto offset3 = *reinterpret_cast<unity::CSharper::String**>(offset2 + 0x20);
            return offset3->ToString();
        } catch (...) {
            return "";
        }
    }

    LevelAPI* GetRoom() {
        try {
            return *reinterpret_cast<LevelAPI**>(reinterpret_cast<std::uint64_t>(this) + 0x60);
        } catch (...) {
            return nullptr;
        }
    }

    void Teleport(unity::CSharper::Vector3 p) {
        try {
            return Tel(this, p);
        }
        catch (...) {
            return;
        }
    }

    bool GetDead() {
        try {
            return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0x28);
        } catch (...) {
            return false;
        }
    }

    void SetDead(bool dead) {
        try {
            *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0x28) = dead;
        }
        catch (...) { }
    }
};