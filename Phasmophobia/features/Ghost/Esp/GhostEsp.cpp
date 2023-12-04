#include "GhostEsp.hpp"
#include "../Ghost.hpp"

static II::Bounds GetEntityMinBounds(II::Collider* entity, float minSize)
{
	const auto entityPosition = entity->GetBounds().m_vCenter;
	return { entityPosition, { minSize, minSize, minSize } };
}

static II::Bounds GetObjectBounds(II::Collider* entity)
{
	const auto gameObject = entity->GetGameObject();
	if (gameObject == nullptr)
		return GetEntityMinBounds(entity, 0.5);

	try {
		// Sometimes occurs access violation in UnityPlayer.dll
		// Callow: Have no idea what to do with it unless just catch exception
		auto bounds = entity->GetBounds();
		if (bounds.m_vExtents.x < 0.5 &&
			bounds.m_vExtents.y < 0.5 &&
			bounds.m_vExtents.z < 0.5)
			bounds.m_vExtents = { 0.5, 0.5, 0.5 };

		const auto min = bounds.m_vExtents - bounds.m_vExtents;
		auto max = bounds.m_vExtents + bounds.m_vExtents;

		// When monster or some another object in a far from player - they disappear
		// And for some reason game object extends
		if ((min.x == 0 || min.y == 0 || min.z == 0))
			return GetEntityMinBounds(entity, 1);

		return bounds;
	} catch (...) {
		return GetEntityMinBounds(entity, 0.5);
	}
}

struct BoxScreen
{
	ImVec2 lowerTopLeft;
	ImVec2 lowerTopRight;
	ImVec2 lowerBottomLeft;
	ImVec2 lowerBottomRight;

	ImVec2 upperTopLeft;
	ImVec2 upperTopRight;
	ImVec2 upperBottomLeft;
	ImVec2 upperBottomRight;
};

static ImVec2 FromVec3(const II::Vector3& vec3)
{
	return { vec3.x, vec3.y };
}

static std::optional<BoxScreen> GetEntityScreenBox(II::Collider* entity)
{
	if (II::Camera::GetMain() == nullptr)
		return {};

	auto [m_vCenter, m_vExtents] = GetObjectBounds(entity);

	auto min = m_vCenter - m_vExtents;
	auto max = m_vCenter + m_vExtents;

	BoxScreen box;
	II::Vector3 temp;
#define BOX_FIELD_SET(field, px, py, pz) temp = II::Camera::GetMain()->WorldToScreenPoint({ px, py, pz }, II::Camera::Eye::Mono);\
			if (temp.z < 1) return {};\
			box.##field = FromVec3(temp);

	BOX_FIELD_SET(lowerTopLeft, min.x, min.y, max.z);
	BOX_FIELD_SET(lowerTopRight, max.x, min.y, max.z);
	BOX_FIELD_SET(lowerBottomLeft, min.x, min.y, min.z);
	BOX_FIELD_SET(lowerBottomRight, max.x, min.y, min.z);

	BOX_FIELD_SET(upperTopLeft, min.x, max.y, max.z);
	BOX_FIELD_SET(upperTopRight, max.x, max.y, max.z);
	BOX_FIELD_SET(upperBottomLeft, min.x, max.y, min.z);
	BOX_FIELD_SET(upperBottomRight, max.x, max.y, min.z);

#undef BOX_FIELD_SET

	return box;
}

static ImVec2 s_ResolutionScale = ImVec2(0, 0);
static ImVec2 s_ScreenResolution = ImVec2(0, 0);

static void ScaleBoxScreen(BoxScreen& boxScreen)
{
	if (s_ResolutionScale.x != 0)
	{

#define SCALE_FIELD(field) boxScreen.##field##.x *= s_ResolutionScale.x; boxScreen.##field##.y *= s_ResolutionScale.y

		SCALE_FIELD(lowerTopLeft);
		SCALE_FIELD(lowerTopRight);
		SCALE_FIELD(lowerBottomLeft);
		SCALE_FIELD(lowerBottomRight);

		SCALE_FIELD(upperTopLeft);
		SCALE_FIELD(upperTopRight);
		SCALE_FIELD(upperBottomLeft);
		SCALE_FIELD(upperBottomRight);

#undef SCALE_FIELD

	}

	auto screenHeight = init_space::Info::h;

#define FIX_Y(field) boxScreen.##field##.y = screenHeight - boxScreen.##field##.y

	FIX_Y(lowerTopLeft);
	FIX_Y(lowerTopRight);
	FIX_Y(lowerBottomLeft);
	FIX_Y(lowerBottomRight);

	FIX_Y(upperTopLeft);
	FIX_Y(upperTopRight);
	FIX_Y(upperBottomLeft);
	FIX_Y(upperBottomRight);
	 
#undef FIX_Y

}

static void UpdateResolutionScale()
{

	s_ResolutionScale = { 0, 0 };

	if (II::Camera::GetMain() == nullptr)
		return;

	auto pixelWidth = init_space::Info::w;
	auto pixelHeight = init_space::Info::h;

	if (pixelWidth == 0 || pixelHeight == 0)
		return;

	auto screenWidth = init_space::Info::w;
	auto screenHeight = init_space::Info::h;

	if (screenWidth == 0 || screenHeight == 0)
		return;

	if (screenHeight == pixelHeight && screenWidth == pixelWidth)
		return;

	s_ScreenResolution.x = static_cast<float>(screenWidth);
	s_ScreenResolution.y = static_cast<float>(screenHeight);

	s_ResolutionScale.x = s_ScreenResolution.x / static_cast<float>(pixelWidth);
	s_ResolutionScale.y = s_ScreenResolution.y / static_cast<float>(pixelHeight);
}

static II::Rect GetEntityScreenRect(const BoxScreen& box, bool scalling = true)
{
	II::Rect boxRect{};
	
	boxRect.fX = box.lowerTopLeft.x < box.lowerTopRight.x ? box.lowerTopLeft.x : box.lowerTopRight.x;

	boxRect.fWidth = box.lowerTopLeft.x >box.lowerTopRight.x ? (box.lowerTopLeft.x) : (box.lowerTopRight.x);

	boxRect.fY = box.lowerTopLeft.y > (box.lowerTopRight.y) ? box.lowerTopLeft.y : (box.lowerTopRight.y);

	boxRect.fHeight = box.lowerTopLeft.y < (box.lowerTopRight.y) ? (box.lowerTopLeft.y) : (box.lowerTopRight.y);

	if (!scalling)
	{
		std::swap(boxRect.fY, boxRect.fHeight);
		return boxRect;
	}

	if (s_ResolutionScale.x != 0)
	{
		boxRect.fX *= s_ResolutionScale.x;
		boxRect.fWidth *= s_ResolutionScale.x;

		boxRect.fY *= s_ResolutionScale.y;
		boxRect.fHeight *= s_ResolutionScale.y;
	}

	auto screenHeight = init_space::Info::h;
	boxRect.fY = screenHeight - boxRect.fY;
	boxRect.fHeight = screenHeight - boxRect.fHeight;
	return boxRect;
}

static auto DrawQuadLines(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col) -> void {
	const auto draw = ImGui::GetBackgroundDrawList();

	draw->AddLine(p1, p2, col);
	draw->AddLine(p2, p3, col);
	draw->AddLine(p3, p4, col);
	draw->AddLine(p4, p1, col);
}

// Callow: This way to drawing is slower than native
static II::Rect DrawBox(II::Collider* entity, const ImColor& color)
{
	auto box = GetEntityScreenBox(entity);
	if (!box)
		return {};

	ScaleBoxScreen(*box);
	auto draw = ImGui::GetBackgroundDrawList();


	DrawQuadLines(box->lowerBottomLeft, box->lowerTopLeft, box->lowerTopRight, box->lowerBottomRight, color);
	DrawQuadLines(box->upperBottomLeft, box->upperTopLeft, box->upperTopRight, box->upperBottomRight, color);

	draw->AddLine(box->lowerBottomLeft, box->upperBottomLeft, color);
	draw->AddLine(box->lowerTopLeft, box->upperTopLeft, color);
	draw->AddLine(box->lowerTopRight, box->upperTopRight, color);
	draw->AddLine(box->lowerBottomRight, box->upperBottomRight, color);

	auto rect = GetEntityScreenRect(*box, false);
	return rect;
}

auto GhostEsp::GetInfo() const -> const GuiInfo& { return *new GuiInfo{ reinterpret_cast<const char*>(u8"鬼魂 (Ghost)"), reinterpret_cast<const char*>(u8"透视 (Esp)"), true, false, true }; }
auto GhostEsp::Draw() -> void {
	if (enable && Ghost::ghost) {
		for (const auto pCollider : Ghost::ghost->GetGameObject()->GetComponentsInChildren<II::Collider*>(I::Get("UnityEngine.PhysicsModule.dll")->Get("Collider"))) {
			UpdateResolutionScale();
			DrawBox(pCollider, ImColor{ 255, 0, 0 });
		}
	}
}
auto GhostEsp::Render() -> void {
	ImGui::Checkbox(U8(u8"启用(Enable)"), &enable);
}
auto GhostEsp::Update() -> void { Feature::Update(); }
auto GhostEsp::Save(nlohmann::json& json) -> void {
	
}
auto GhostEsp::Load(nlohmann::json& json) -> void {

}
auto GhostEsp::GetInstance() -> GhostEsp* {
	static GhostEsp ghost_esp;
	return &ghost_esp;
}
