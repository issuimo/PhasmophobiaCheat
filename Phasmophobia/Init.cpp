#include "Init.h"

#include "features/Ghost/Ghost.hpp"
#include "features/Ghost/Behavior/GhostBehavior.h"
#include "features/Ghost/Esp/GhostEsp.hpp"
#include "features/Ghost/Features/GhostFeatures.hpp"
#include "features/Ghost/List/GhostList.hpp"
#include "features/Ghost/Properties/GhostProperties.h"
#include "features/Players/Behavior/PlayerBehavior.hpp"
#include "features/Players/Features/PlayerFeatures.h"
#include "features/Players/List/PlayerList.hpp"
#include "features/Players/Properties/PlayerProperties.h"
#include "features/Rooms/List/RoomList.hpp"

namespace init_space {
#define ADD(name) features[name::GetInstance()->GetInfo().tableName].push_back(reinterpret_cast<Feature*>(name::GetInstance()))

	auto Feature::Init() -> void {
		Player::InitOnce();
		Room::InitOnce();
		GhostAI::InitOnce();

		ADD(RoomList);
		ADD(GhostList);
		ADD(GhostEsp);
		ADD(GhostBehavior);
		ADD(GhostProperties);
		ADD(GhostFeatures);
		ADD(PlayerList);
		ADD(PlayerBehavior);
		ADD(PlayerFeatures);
		ADD(PlayerProperties);
	}
}
