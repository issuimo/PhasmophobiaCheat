#include "IteamList.h"

#include "PlayerList.h"

auto PhotonObjectInteract::PhotonObjectInteract_Awake_NEW(void* p) -> void {
    std::lock_guard lock(mutex);
    iteams.push_back(p);
    HookManager::Call(PhotonObjectInteract_Awake_NEW, p);
}

auto PhotonObjectInteract::PhotonObjectInteract_OnDestroy_NEW(void* p) -> void {
    std::lock_guard lock(mutex);
    const auto      it = std::ranges::find(iteams, p);
    if (it != iteams.end())
        iteams.erase(it);
    return HookManager::Call(PhotonObjectInteract_OnDestroy_NEW, p);
}

PhotonObjectInteract::PhotonObjectInteract() : Feature{} {
     HookManager::Install(reinterpret_cast<void(*)(void*)>(unity::Il2cpp::Method::GetAddress("PhotonObjectInteract", "Awake", 0)), PhotonObjectInteract_Awake_NEW);
     HookManager::Install(reinterpret_cast<void(*)(void*)>(unity::Il2cpp::Method::GetAddress("PhotonObjectInteract", "OnDestroy", 0)), PhotonObjectInteract_OnDestroy_NEW);
}

auto PhotonObjectInteract::GetInstance() -> PhotonObjectInteract& {
    static PhotonObjectInteract Instance;
    return Instance;
}

auto PhotonObjectInteract::GetInfo() const -> const GuiInfo& {
    static GuiInfo info{ reinterpret_cast<const char*>(u8"物品"), reinterpret_cast<const char*>(u8"物品列表"), true };
    return info;
}

auto PhotonObjectInteract::Render() -> void {
    if (ImGui::BeginTable("PlayerList",
        3,
        ImGuiTableFlags_ScrollX | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollY |
        ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
        ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable,
        ImVec2(0.0F, ImGui::GetTextLineHeightWithSpacing() * 8))) {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"名称"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"地址"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"操作"), ImGuiTableColumnFlags_None);
        ImGui::TableHeadersRow();

        std::lock_guard lock(mutex);
        for (const auto& actor : iteams) {
            ImGui::TableNextRow();

            ImGui::PushID(actor);
            try {
                if (ImGui::TableSetColumnIndex(0)) {
                    try {
                        ImGui::Text("");
                    }
                    catch (...) {}
                }
                if (ImGui::TableSetColumnIndex(1)) {
                    try {
                        ImGui::Text(std::format("{:#x}", reinterpret_cast<std::uint64_t>(actor)).c_str());
                    }
                    catch (...) {}
                }
                if (ImGui::TableSetColumnIndex(2)) {
                    try {
                        if (ImGui::SmallButton("Add")) {
                            auto players = PlayerList::GetPlayers();
                            for (auto& player : players) {
                                const auto pPropGrab = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint64_t>(player) + 0x128);
                                std::cout << pPropGrab << std::endl;
                                const auto list1 = *reinterpret_cast<std::int64_t*>(pPropGrab + 0x48);
                                const auto list = *reinterpret_cast<unity::CSharper::List<std::int64_t*>**>(list1 + 0x10);
                                std::cout << list << std::endl;
                                std::cout << list->GetCount() << std::endl;
                            }
                        }
                    }
                    catch (...) {}
                }
            }
            catch (...) {}
            ImGui::PopID();
        }

        ImGui::EndTable();
    }
}

auto PhotonObjectInteract::Update() -> void { }

auto PhotonObjectInteract::DrawStatus() -> void {}

auto PhotonObjectInteract::Save(nlohmann::json& json) -> void {

}

auto PhotonObjectInteract::Load(nlohmann::json& json) -> void {

}
