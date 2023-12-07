#include "Room.hpp"

auto Room::InitOnce() -> void {
	if (const auto pClass = I::Get("Assembly-CSharp.dll")->Get("LevelRoom")) {
		mAwake = pClass->Get<IM>("Awake")->Cast<void, Room*>();
	}

	if (mAwake) {
		H::Install(mAwake, HAwake);
	}
}

auto Room::HAwake(Room* _this) -> void {
	std::lock_guard lock(Room::roomsMutex);
	rooms.push_back(_this);
	H::Fcall(HAwake, _this);
}
