#pragma once
#include "../Init.h"

class CursedItems final : public init_space::Feature {
public:
    static auto GetInstance() -> CursedItems&;
    auto        GetInfo() const -> const GuiInfo & override;
    auto        Render() -> void override;
    auto        Update() -> void override;
    auto        DrawStatus() -> void override;
    auto        Save(nlohmann::json& json) -> void override;
    auto        Load(nlohmann::json& json) -> void override;

protected:
    static auto MusicBox_BreakMusicBox_NEW(void* p, bool arg) -> void;
    static auto MusicBox_TryBreakMusicBox_NEW(void* p, bool arg) -> void;
    static auto HauntedMirror_BreakItem_NEW(void* p) -> void;
    CursedItems();

private:
    inline static bool musicBox, hauntedMirror;
};
