#pragma once
#include "../Init.h"

#include "../gameAPI/PlayerAPI.h"

class PlayerList final : public initSpace::Feature {
public:
    static auto GetInstance() -> PlayerList&;
    auto        GetInfo() const -> const GuiInfo& override;
    auto        Render() -> void override;
    auto        Update() -> void override;
    auto        DrawStatus() -> void override;
    auto        Save(nlohmann::json& json) -> void override;
    auto        Load(nlohmann::json& json) -> void override;

    static auto GetPlayers() {
        std::lock_guard lock(mutex);
        return players;
    }

protected:
    PlayerList();
    static auto Player_Awake_NEW(PlayerAPI* player) -> void;
    static auto Player_OnDestroy_NEW(PlayerAPI* player) -> void;

    inline static void(*RevivePlayer)(void*);
    inline static void(*StartKillingPlayer)(void*);
private:
    inline static std::mutex              mutex;
    inline static std::vector<PlayerAPI*> players;
};
