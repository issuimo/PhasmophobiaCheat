#include "RoomList.hpp"

auto RoomList::GetInfo() const -> const GuiInfo& {
	return *new GuiInfo{ reinterpret_cast<const char*>(u8"房间 (Rooms)"), reinterpret_cast<const char*>(u8"列表 (List)"), true, false, false };
}
auto RoomList::Draw() -> void { Feature::Draw(); }
auto RoomList::Render() -> void {
	if (ImGui::BeginTable("RoomList", 1,
		ImGuiTableFlags_ScrollX | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollY |
		ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
		ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable,
		ImVec2(0.0F, ImGui::GetTextLineHeightWithSpacing() * 16))) {
		ImGui::TableSetupScrollFreeze(1, 1);
		ImGui::TableSetupColumn(reinterpret_cast<const char*>(u8"名称 (name)"), ImGuiTableColumnFlags_None);

		ImGui::TableHeadersRow();

		std::lock_guard lock(Room::roomsMutex);
		for (const auto& room : Room::rooms) {
			ImGui::TableNextRow();
			ImGui::PushID(room);
			if (room->name) if (ImGui::TableSetColumnIndex(0)) ImGui::Text(std::format("{}", room->name->ToString()).c_str());
			ImGui::PopID();
		}

		ImGui::EndTable();
	}
}
auto RoomList::Update() -> void { Feature::Update(); }
auto RoomList::Save(nlohmann::json& json) -> void { Feature::Save(json); }
auto RoomList::Load(nlohmann::json& json) -> void { Feature::Load(json); }
auto RoomList::GetInstance() -> RoomList* {
	static RoomList players;
	return &players;
}
