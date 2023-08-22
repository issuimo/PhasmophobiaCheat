#pragma once
#include <future>
#include <thread>
#include <iostream>
#include <windows.h>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <mutex>
#include <vector>
#include <unordered_map>
#include "library/json.hpp"
#include "library/detours/HookManager.h"
#include "library/imgui/imgui.h"
#include "library/UnityHack.h"
#include "library/imgui/implot.h"

namespace initSpace {
    inline static struct {
        bool mainShow;
        bool imGuiInit;
        bool tipsShow;
    } guiInfo;

    class Feature {
    public:
        Feature(const Feature&)                = delete;
        auto operator=(const Feature&) -> void = delete;

        struct GuiInfo {
            std::string tableName;
            std::string groupName;
            bool        needGroup;
        };

        virtual auto GetInfo() const -> const GuiInfo& = 0;
        virtual auto DrawStatus() -> void { };
        virtual auto Render() -> void {};
        virtual auto Update() -> void {};
        virtual auto Save(nlohmann::json& json) -> void {};
        virtual auto Load(nlohmann::json& json) -> void {};

        inline static std::unordered_map<std::string, std::list<Feature*>> features;
        static auto                                                        Init() -> void;

    protected:
        ~Feature() = default;
        Feature()  = default;
    };
}

extern void AntiAntiCheat();