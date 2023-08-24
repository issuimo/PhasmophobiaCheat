#pragma once
#include "../Init.h"

#include "../gameAPI/LevelAPI.h"

class RoomList final : public initSpace::Feature {
public:
    static auto GetInstance() -> RoomList&;
    auto        GetInfo() const -> const GuiInfo & override;
    auto        Render() -> void override;
    auto        Update() -> void override;
    auto        DrawStatus() -> void override;
    auto        Save(nlohmann::json& json) -> void override;
    auto        Load(nlohmann::json& json) -> void override;

    static auto GetRooms() {
        std::lock_guard lock(mutex);
        return rooms;
    }

    static auto ClearRooms() -> void {
        std::lock_guard lock(mutex);
        rooms.clear();
    }

protected:
    static auto LevelRoom_Awake_NEW(LevelAPI* levelApi) -> void;
    RoomList();
private:
    inline static std::mutex              mutex;
    inline static std::vector<LevelAPI*> rooms;
};
