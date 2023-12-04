#pragma once
#ifndef PLAYER
#define PLAYER
#include "../../Init.h"
#include "../Rooms/Room.hpp"

#pragma pack(8)
class Player : public II::MonoBehaviour {
public:
	struct : MonoBehaviour {
		char space1[0x50];
		struct : MonoBehaviour {
			II::String* name;
		}*ptr;
	}*photonView;
	bool dead;
	char space2[0x30];
	Room* levelRoom;
	char space3[0x70];
	struct : MonoBehaviour {
		char space1[0x110];
		struct TMP_Text {
			char space1[0xE0];
			II::String* text;
		};

		struct TextMeshProUGUI : TMP_Text {

		}*textMeshProUgui;
	}*journalController;

	static auto InitOnce() -> void;
	inline static std::vector<Player*> players{};
	inline static std::mutex           playersMutex;

	inline static IM* mTeleport{};

	inline static IM::MethodPointer<void, Player*> mStartKillingPlayer{};
	inline static IM::MethodPointer<void, Player*, bool> mKillPlayer{};
	inline static IM::MethodPointer<void, Player*, bool, void*> mDead{};
	inline static IM::MethodPointer<void, Player*> mDeadRoomEffects{};
private:
	inline static IM::MethodPointer<void, Player*> mAwake{};
	inline static auto UNITY_CALLING_CONVENTION  HAwake(Player* _this) -> void;
	inline static IM::MethodPointer<void, Player*> mOnDestroy{};
	inline static auto UNITY_CALLING_CONVENTION  HOnDestroy(Player* _this) -> void;
};

#endif