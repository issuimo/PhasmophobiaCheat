#include "Player.hpp"

#include "../Ghost/Ghost.hpp"

auto Player::InitOnce() -> void {
	if (const auto pClass = I::Get("Assembly-CSharp.dll")->Get("Player")) {
		mAwake = pClass->Get<IM>("Awake")->Cast<void, Player*>();
		mOnDestroy = pClass->Get<IM>("OnDestroy")->Cast<void, Player*>();

		mTeleport = pClass->Get<IM>("Teleport");
	}

	if (mAwake && mOnDestroy) {
		H::Install(mAwake, HAwake);
		H::Install(mOnDestroy, HOnDestroy);
	}
}

auto UNITY_CALLING_CONVENTION Player::HAwake(Player* _this) -> void {
	std::lock_guard lock(playersMutex);
	players.push_back(_this);
	H::Fcall(HAwake, _this);
}

auto UNITY_CALLING_CONVENTION Player::HOnDestroy(Player* _this) -> void {
	std::lock_guard lock(playersMutex);
	if (const auto it = std::ranges::find(players, _this); it != players.end()) players.erase(it);
	if (players.empty()) {
		Ghost::ghost = nullptr;
		Room::rooms.clear();
	}
	H::Fcall(HAwake, _this);
}
