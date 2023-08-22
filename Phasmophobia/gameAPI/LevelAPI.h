#pragma once
#include <string>
#include "../library/UnityHack.h"
class LevelAPI {
public:
    std::string GetName() {
        try {
            return (*reinterpret_cast<unity::CSharper::IL2cpp::String**>(reinterpret_cast<std::uint64_t>(this) + levelRoomNameOffset))->ToString();
        } catch (...) {
            return "";
        }
    }
private:
    inline static std::uintptr_t levelRoomNameOffset{ 0x68 };
};
