#pragma once
#include "../Init.h"

#include "../gameAPI/CursedItemsControllerAPI.h"

class ESP final : public init_space::Feature {
public:
    static auto GetInstance() -> ESP&;
    auto        GetInfo() const -> const GuiInfo & override;
    auto        Render() -> void override;
    auto        Update() -> void override;
    auto        DrawStatus() -> void override;
    auto        Save(nlohmann::json& json) -> void override;
    auto        Load(nlohmann::json& json) -> void override;

    static auto ClearAllAddress() -> void {
        CursedItemsControllerAPI::hauntedMirror_ = 0;
        CursedItemsControllerAPI::monkeyPaw_ = 0;
        CursedItemsControllerAPI::musicBox_ = 0;
        CursedItemsControllerAPI::ouijaBoard_ = 0;
        CursedItemsControllerAPI::summoningCircle_ = 0;
        CursedItemsControllerAPI::tarotCards_ = 0;
        CursedItemsControllerAPI::voodooDoll_ = 0;
    }
protected:
    static auto MusicBox_ctor_NEW(void* p, unity::CSharper::Vector3 v) -> void;
    static auto VoodooDoll_ctor_NEW(void* p, unity::CSharper::Vector3 v) -> void;
    static auto MonkeyPaw_ctor_NEW(void* p, unity::CSharper::Vector3 v) -> void;
    static auto HauntedMirror_ctor_NEW(void* p, unity::CSharper::Vector3 v) -> void;
    static auto OuijaBoard_Awake_NEW(void* p) -> void;
    static auto SummoningCircle_ctor_NEW(void* p, unity::CSharper::Vector3 v) -> void;
    static auto TarotCard_Awake_NEW(void* p) -> void;
    ESP();
private:
    inline static bool ghostEsp, doorEsp, gRoomEsp, curseObj, playerEsp;
};
