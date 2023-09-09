#pragma once
#include "../Init.h"

class PhotonObjectInteract final : public initSpace::Feature {
public:
    static auto GetInstance() -> PhotonObjectInteract&;
    auto        GetInfo() const -> const GuiInfo & override;
    auto        Render() -> void override;
    auto        Update() -> void override;
    auto        DrawStatus() -> void override;
    auto        Save(nlohmann::json& json) -> void override;
    auto        Load(nlohmann::json& json) -> void override;

protected:
    static auto PhotonObjectInteract_Awake_NEW(void* p) -> void;
    static auto PhotonObjectInteract_OnDestroy_NEW(void* p) -> void;
    PhotonObjectInteract();

private:
    inline static std::mutex mutex;
    inline static std::vector<void*> iteams;
};
