#pragma once
#include "../Init.h"

class ESP final : public initSpace::Feature {
public:
    static auto GetInstance() -> ESP&;
    auto        GetInfo() const -> const GuiInfo & override;
    auto        Render() -> void override;
    auto        Update() -> void override;
    auto        DrawStatus() -> void override;
    auto        Save(nlohmann::json& json) -> void override;
    auto        Load(nlohmann::json& json) -> void override;

    static auto ClearAllAdress() -> void {
        CursedItemsController_This = 0;
    }
protected:
    static auto CursedItemsController_Awake_NEW(void* p) -> void;
    ESP();
private:
    inline static bool ghostEsp, doorEsp, gRoomEsp, curseObj;
    inline static std::uintptr_t CursedItemsController_This;
};
