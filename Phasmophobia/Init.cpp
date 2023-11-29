#include "Init.h"

#include "features/GhostList.h"
#include "features/HighSpeed.h"
#include "features/NoDead.h"
#include "features/PlayerList.h"

#include <TlHelp32.h>

#include "features/CursedItems.h"
#include "features/DoorList.h"
#include "features/ESP.h"
#include "features/Ghost.h"
#include "features/IteamList.h"
#include "features/MoreXP.h"
#include "features/RoomList.h"

namespace init_space {
#define ADD(name) Feature::features[name::GetInstance().GetInfo().tableName].push_back(&name::GetInstance())

	auto Feature::Init() -> void {
		ADD(PlayerList);
		ADD(HighSpeed);
		ADD(NoDead);
		ADD(GhostList);
		ADD(Ghost);
		ADD(ESP);
		ADD(MoreXP);
		ADD(DoorList);
		ADD(RoomList);
		ADD(CursedItems);
		ADD(PhotonObjectInteract);
	}
}
