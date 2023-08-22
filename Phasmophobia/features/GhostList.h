#pragma once
#include "../Init.h"

#include "../gameAPI/GhostAPI.h"

class GhostList final : public initSpace::Feature {
public:
    static auto GetInstance() -> GhostList&;
    auto        GetInfo() const -> const GuiInfo & override;
    auto        Render() -> void override;
    auto        Update() -> void override;
    auto        DrawStatus() -> void override;
    auto        Save(nlohmann::json& json) -> void override;
    auto        Load(nlohmann::json& json) -> void override;

    static auto GetGhosts() {
        std::lock_guard lock(mutex);
        return ghosts;
    }

    static auto ClearVector() {
        std::lock_guard lock(mutex);
        ghosts.clear();
    }
protected:
    static auto Ghost_Awake_NEW(GhostAPI* class_) -> void;
    GhostList();
    void* (*StartHuntingTimer)(void*);
private:
    inline static std::mutex             mutex;
    inline static std::vector<GhostAPI*> ghosts;
};
