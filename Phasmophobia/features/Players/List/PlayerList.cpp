#include "PlayerList.hpp"

PlayerList::PlayerList() = default;

auto PlayerList::GetInfo() const -> const GuiInfo& {
	return *new GuiInfo{ reinterpret_cast<const char*>(u8"玩家 (Players)"), reinterpret_cast<const char*>(u8"列表 (List)"), true, false, false };
}

auto PlayerList::Draw() -> void { Feature::Draw(); }

auto PlayerList::Render() -> void {
    if (ImGui::BeginTable("PlayerList",3,
        ImGuiTableFlags_ScrollX | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollY |
        ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
        ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable,
        ImVec2(0.0F, ImGui::GetTextLineHeightWithSpacing() * 8))) {
        ImGui::TableSetupScrollFreeze(1, 1);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"名称 (name)"), ImGuiTableColumnFlags_None);
		ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"死亡 (dead)"), ImGuiTableColumnFlags_None);
		ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"房间 (room)"), ImGuiTableColumnFlags_None);
        ImGui::TableHeadersRow();

        std::lock_guard lock(Player::playersMutex);
        for (const auto& player : Player::players) {
			ImGui::TableNextRow();
			ImGui::PushID(player);
			if (player->photonView && player->photonView->ptr && player->photonView->ptr->name && player->levelRoom && player->levelRoom->name) {
				try {
					if (ImGui::TableSetColumnIndex(0)) ImGui::Text(std::format("{}", player->photonView->ptr->name->ToString()).c_str());
					if (ImGui::TableSetColumnIndex(1)) ImGui::Text(std::format("{}", player->dead).c_str());
					if (ImGui::TableSetColumnIndex(2)) ImGui::Text(std::format("{}", player->levelRoom->name->ToString()).c_str());
				}
				catch (...) {}
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
