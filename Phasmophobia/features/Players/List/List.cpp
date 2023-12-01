#include "List.hpp"

PlayerList::PlayerList() {
	if (const auto pClass = I::Get("Assembly-CSharp.dll")->Get("Player")) {
		mAwake     = pClass->Get<IM>("Awake")->Cast<void, void*>();
		mOnDestroy = pClass->Get<IM>("OnDestroy")->Cast<void, void*>();

		Player::mTeleport = pClass->Get<IM>("Teleport");
	}

	if (CheckNull(mAwake, mOnDestroy)) {
		H::Install(mAwake, HAwake);
		H::Install(mOnDestroy, HOnDestroy);
	}
}

auto PlayerList::GetInfo() const -> const GuiInfo& {
	return *new GuiInfo{ reinterpret_cast<const char*>(u8"玩家 (Players)"), reinterpret_cast<const char*>(u8"列表 (List)"), true, false, false };
}

auto PlayerList::Draw() -> void { Feature::Draw(); }

auto PlayerList::Render() -> void {
    if (ImGui::BeginTable("PlayerList",5,
        ImGuiTableFlags_ScrollX | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollY |
        ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
        ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable,
        ImVec2(0.0F, ImGui::GetTextLineHeightWithSpacing() * 8))) {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"地址"), ImGuiTableColumnFlags_None);
        ImGui::TableHeadersRow();

        std::lock_guard lock(Player::playersMutex);
        for (const auto& player : Player::players) {
            ImGui::TableNextRow();
            ImGui::PushID(player);
            if (ImGui::TableSetColumnIndex(0)) {
                ImGui::Text(std::format("{}", static_cast<void*>(player)).c_str());
            }
            ImGui::PopID();
        }

        ImGui::EndTable();
    }
}

auto PlayerList::Update() -> void { Feature::Update(); }
auto PlayerList::Save(nlohmann::json& json) -> void { Feature::Save(json); }
auto PlayerList::Load(nlohmann::json& json) -> void { Feature::Load(json); }

auto PlayerList::GetInstance() -> PlayerList* {
	static PlayerList players;
	return &players;
}

auto UNITY_CALLING_CONVENTION PlayerList::HAwake(void* _this) -> void {
	std::lock_guard lock(Player::playersMutex);
	Player::players.push_back(_this);
	H::Fcall(HAwake, _this);
}

auto UNITY_CALLING_CONVENTION PlayerList::HOnDestroy(void* _this) -> void {
	std::lock_guard lock(Player::playersMutex);
	if (const auto it = std::ranges::find(Player::players, _this); it != Player::players.end()) Player::players.erase(it);
	H::Fcall(HAwake, _this);
}