#pragma once
#ifndef PLAYER
#define PLAYER
#include "../../Init.h"

class Player : II::MonoBehaviour {
public:
	struct PhotonView : MonoBehaviour {
		
	}photonView;

	inline static std::vector<void*> players{};
	inline static std::mutex         playersMutex;

	inline static IM* mTeleport{};
};

#endif