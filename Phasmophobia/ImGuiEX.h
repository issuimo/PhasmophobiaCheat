#pragma once
#ifndef IMGUIEX
#define IMGUIEX
#include <Windows.h>
#include <cstdint>

#include "library/imgui/imgui.h"
#include "library/imgui/imgui_internal.h"

namespace ImGuiEx {
	enum class OutlineSide : uint32_t {
		Left   = 1,
		Right  = 2,
		Top    = 4,
		Bottom = 8,
		All    = Left | Right | Top | Bottom
	};

	static auto DrawQuadLines(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col) -> void {
		const auto draw = ImGui::GetBackgroundDrawList();
		draw->AddLine(p1, p2, col);
		draw->AddLine(p2, p3, col);
		draw->AddLine(p3, p4, col);
		draw->AddLine(p4, p1, col);
	}

	static bool operator&(OutlineSide lhs, OutlineSide rhs) {
		return
			static_cast<std::underlying_type<OutlineSide>::type>(lhs) &
			static_cast<std::underlying_type<OutlineSide>::type>(rhs);
	}

	static auto DrawTextWithOutline(ImDrawList* drawList, ImFont* font, float fontSize, const ImVec2& screenPos, const char* text, const ImColor& textColor, float outlineThickness, OutlineSide sides, const ImColor& outlineColor) -> void {
		if (outlineThickness == 0.0f) drawList->AddText(font, fontSize, screenPos, outlineColor, text);
		else {
			if (sides & OutlineSide::Left)
				drawList->AddText(font, fontSize, {screenPos.x - outlineThickness, screenPos.y}, outlineColor, text);

			if (sides & OutlineSide::Right)
				drawList->AddText(font, fontSize, {screenPos.x + outlineThickness, screenPos.y}, outlineColor, text);

			if (sides & OutlineSide::Bottom)
				drawList->AddText(font, fontSize, {screenPos.x, screenPos.y - outlineThickness}, outlineColor, text);

			if (sides & OutlineSide::Top)
				drawList->AddText(font, fontSize, {screenPos.x, screenPos.y + outlineThickness}, outlineColor, text);
		}

		drawList->AddText(font, fontSize, screenPos, textColor, text);
	}

	static auto DrawTextWithOutline(ImDrawList* drawList, const ImVec2& screenPos, const char* text, const ImColor& textColor, float outlineThickness, OutlineSide sides, const ImColor& outlineColor) -> void { DrawTextWithOutline(drawList, nullptr, 0.0f, screenPos, text, textColor, outlineThickness, sides, outlineColor); }

	static auto ShowHelpText(const char* text) -> void {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(text);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

	static auto HelpMarker(const char* desc) -> void {
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered()) ShowHelpText(desc);
	}

	static auto AddUnderLine(ImColor col_) -> void {
		auto       min = ImGui::GetItemRectMin();
		const auto max = ImGui::GetItemRectMax();
		min.y          = max.y;
		ImGui::GetWindowDrawList()->AddLine(min, max, col_, 1.0f);
	}

	static auto TextURL(const char* name, const wchar_t* url, const bool SameLineBefore_, const bool SameLineAfter_) -> void {
		if (SameLineBefore_) ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered]);
		ImGui::Text(name);
		ImGui::PopStyleColor();
		if (ImGui::IsItemHovered()) {
			if (ImGui::IsMouseClicked(0))
				ShellExecute(nullptr, nullptr, url, nullptr, nullptr, SW_SHOW);
			AddUnderLine(ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered]);
			ImGui::SetTooltip("Open in browser\n%s", url);
		} else AddUnderLine(ImGui::GetStyle().Colors[ImGuiCol_Button]);
		if (SameLineAfter_) ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
	}
}

#endif
