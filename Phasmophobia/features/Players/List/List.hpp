#ifndef PLAYERS_LIST
#define PLAYERS_LIST
#include "../../../Init.h"
#include "../Player.hpp"

class PlayerList : init_space::Feature {
public:
	PlayerList();
	~PlayerList() = default;
	[[nodiscard]] auto GetInfo() const -> const GuiInfo& override;
	auto               Draw() -> void override;
	auto               Render() -> void override;
	auto               Update() -> void override;
	auto               Save(nlohmann::json& json) -> void override;
	auto               Load(nlohmann::json& json) -> void override;

	static auto GetInstance() -> PlayerList*;
private:
	inline static IM::MethodPointer<void, void*> mAwake{};
	inline static auto UNITY_CALLING_CONVENTION  HAwake(void* _this) -> void;
	inline static IM::MethodPointer<void, void*> mOnDestroy{};
	inline static auto UNITY_CALLING_CONVENTION  HOnDestroy(void* _this) -> void;
};
#endif
