#include "GhostList.hpp"

#include "../Ghost.hpp"

#include "../../Players/Player.hpp"

auto GhostList::GetInfo() const -> const GuiInfo& {
	return *new GuiInfo{ reinterpret_cast<const char*>(u8"鬼魂 (Ghost)"), reinterpret_cast<const char*>(u8"列表 (List)"), true, false, false };
}
auto GhostList::Draw() -> void { Feature::Draw(); }
auto GhostList::Render() -> void {
    if (ImGui::BeginTable("GhostList", 8,
        ImGuiTableFlags_ScrollX | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollY |
        ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
        ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_SizingFixedSame,
        ImVec2(0.0F, ImGui::GetTextLineHeightWithSpacing() * 8))) {
        ImGui::TableSetupScrollFreeze(1, 1);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"序号 (index)"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"名称 (name)"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"猎杀 (hunt)"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"房间 (room)"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"速度 (speed)"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"类型 (type)"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"状态 (state)"), ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"证据 (proof)"), ImGuiTableColumnFlags_None);
        ImGui::TableHeadersRow();

        std::lock_guard lock(Player::playersMutex);
		if (!Player::players.empty())
			if (Ghost::ghost)
				try {
				if (Ghost::ghost->ghostInfo)
					if (Ghost::ghost->ghostInfo->room)
						if (Ghost::ghost->ghostInfo->room->name && Ghost::ghost->ghostInfo->proof && Player::players[0]->journalController && Player::players[0]->journalController->textMeshProUgui) {
							ImGui::TableNextRow();
							ImGui::PushID(Ghost::ghost);
							if (ImGui::TableSetColumnIndex(0)) ImGui::Text(std::format("{}", static_cast<int>(Ghost::ghost->ghostInfo->ghostType)).c_str());
							if (ImGui::TableSetColumnIndex(1)) ImGui::Text(std::format("{}", Player::players[0]->journalController->textMeshProUgui->text->ToString()).c_str());
							if (ImGui::TableSetColumnIndex(2)) ImGui::Text(std::format("{}", Ghost::ghost->hunt).c_str());
							if (ImGui::TableSetColumnIndex(3)) ImGui::Text(std::format("{}", Ghost::ghost->ghostInfo->room->name->ToString()).c_str());
							if (ImGui::TableSetColumnIndex(4)) ImGui::Text(std::format("{}", Ghost::ghost->speed).c_str());
							if (ImGui::TableSetColumnIndex(5)) ImGui::Text(std::format("{}", Ghost::ghost->ghostInfo->ghostType).c_str());
							if (ImGui::TableSetColumnIndex(6)) ImGui::Text(std::format("{}", Ghost::ghost->ghostState).c_str());
							if (ImGui::TableSetColumnIndex(7)) for (const auto proof : Ghost::ghost->ghostInfo->proof->ToArray()->ToVector()) ImGui::Text(std::format("{} ", magic_enum::enum_name<Ghost::Proof>(proof)).c_str());
							ImGui::PopID();
						}
				} catch (...) {}

		ImGui::EndTable();
    }
}
auto GhostList::Update() -> void { Feature::Update(); }
auto GhostList::Save(nlohmann::json& json) -> void { Feature::Save(json); }
auto GhostList::Load(nlohmann::json& json) -> void { Feature::Load(json); }
auto GhostList::GetInstance() -> GhostList* {
	static GhostList players;
	return &players;
}
