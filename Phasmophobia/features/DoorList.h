#pragma once
#include "../Init.h"

#include "../gameAPI/DoorAPI.h"

class DoorList final : public init_space::Feature {
public:
    static auto GetInstance() -> DoorList&;
    auto        GetInfo() const -> const GuiInfo & override;
    auto        Render() -> void override;
    auto        Update() -> void override;
    auto        DrawStatus() -> void override;
    auto        Save(nlohmann::json& json) -> void override;
    auto        Load(nlohmann::json& json) -> void override;

    static auto GetDoors() {
        std::lock_guard lock(mutex);
        return doors;
    }

    static auto ClearVector() {
        std::lock_guard lock(mutex);
        doors.clear();
    }
protected:
    static auto Door_Awake_NEW(DoorAPI* doorApi) -> void;
    DoorList();
private:
    inline static std::mutex            mutex;
    inline static std::vector<DoorAPI*> doors;
};
