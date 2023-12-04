#pragma once
#ifndef ROOM
#define ROOM
#include "../../Init.h"

#pragma pack(8)
class Room : public II::MonoBehaviour {
public:
	char space1[0x48];
	II::String* name;

	static auto InitOnce() -> void;
	inline static std::vector<Room*> rooms{};
	inline static std::mutex         roomsMutex;

private:
	inline static IM::MethodPointer<void, Room*> mAwake{};
	inline static auto UNITY_CALLING_CONVENTION  HAwake(Room* _this) -> void;
};

#endif