#include "Init.h"

#include "features/Ghost/Ghost.hpp"
#include "features/Ghost/Esp/GhostEsp.hpp"
#include "features/Ghost/List/GhostList.hpp"
#include "features/Players/List/PlayerList.hpp"
#include "features/Players/NoDead/NoDead.hpp"
#include "features/Rooms/List/RoomList.hpp"

namespace init_space {
#define ADD(name) features[name::GetInstance()->GetInfo().tableName].push_back(reinterpret_cast<Feature*>(name::GetInstance()))

	auto Feature::Init() -> void {
		Player::InitOnce();
		Room::InitOnce();
		Ghost::InitOnce();

		ADD(RoomList);
		ADD(GhostList);
		ADD(GhostEsp);
		ADD(PlayerList);
		ADD(PlayerNoDead);
	}
}
