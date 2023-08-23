#pragma once
#include "../library/UnityHack.h"
class CursedItemsControllerAPI {
public:
    inline static std::uintptr_t hauntedMirror_;
    inline static std::uintptr_t musicBox_;
    inline static std::uintptr_t monkeyPaw_;
    inline static std::uintptr_t ouijaBoard_;
    inline static std::uintptr_t summoningCircle_;
    inline static std::uintptr_t tarotCards_;
    inline static std::uintptr_t voodooDoll_;

    static void* hasHauntedMirror() {
        try {
            return reinterpret_cast<void*>(hauntedMirror_);
        } catch (...) {
            return nullptr;
        }
    }

    static void* hasMusicBox() {
        try {
            return reinterpret_cast<void*>(musicBox_);
        }
        catch (...) {
            return nullptr;
        }
    }

    static void* hasMonkeyPaw() {
        try {
            return reinterpret_cast<void*>(monkeyPaw_);
        }
        catch (...) {
            return nullptr;
        }
    }

    static void* hasOuijaBoard() {
        try {
            return reinterpret_cast<void*>(ouijaBoard_);
        }
        catch (...) {
            return nullptr;
        }
    }

    static void* hasSummoningCircle() {
        try {
            return reinterpret_cast<void*>(summoningCircle_);
        }
        catch (...) {
            return nullptr;
        }
    }

    static void* hasTarotCards() {
        try {
            return reinterpret_cast<void*>(tarotCards_);
        }
        catch (...) {
            return nullptr;
        }
    }

    static void* hasVoodooDoll() {
        try {
            return reinterpret_cast<void*>(voodooDoll_);
        }
        catch (...) {
            return nullptr;
        }
    }
};