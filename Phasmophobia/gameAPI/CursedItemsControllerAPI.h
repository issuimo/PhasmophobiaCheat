#pragma once
#include "../library/UnityHack.h"
class CursedItemsControllerAPI {
public:
    void* hasHauntedMirror() {
        try {
            return *reinterpret_cast<void**>(reinterpret_cast<std::uint64_t>(this) + 0x40);
        } catch (...) {
            return nullptr;
        }
    }

    void* hasMusicBox() {
        try {
            return *reinterpret_cast<void**>(reinterpret_cast<std::uint64_t>(this) + 0x28);
        }
        catch (...) {
            return nullptr;
        }
    }

    void* hasMonkeyPaw() {
        try {
            return *reinterpret_cast<void**>(reinterpret_cast<std::uint64_t>(this) + 0x50);
        }
        catch (...) {
            return nullptr;
        }
    }

    void* hasOuijaBoard() {
        try {
            return *reinterpret_cast<void**>(reinterpret_cast<std::uint64_t>(this) + 0x20);
        }
        catch (...) {
            return nullptr;
        }
    }

    void* hasSummoningCircle() {
        try {
            return *reinterpret_cast<void**>(reinterpret_cast<std::uint64_t>(this) + 0x38);
        }
        catch (...) {
            return nullptr;
        }
    }

    void* hasTarotCards() {
        try {
            return *reinterpret_cast<void**>(reinterpret_cast<std::uint64_t>(this) + 0x30);
        }
        catch (...) {
            return nullptr;
        }
    }

    void* hasVoodooDoll() {
        try {
            return *reinterpret_cast<void**>(reinterpret_cast<std::uint64_t>(this) + 0x48);
        }
        catch (...) {
            return nullptr;
        }
    }
};