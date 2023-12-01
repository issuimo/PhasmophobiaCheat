#include "Init.h"

#include "features/Players/List/List.hpp"
namespace init_space {
#define ADD(name) features[name::GetInstance()->GetInfo().tableName].push_back(reinterpret_cast<Feature*>(name::GetInstance()))

	auto Feature::Init() -> void {
		ADD(PlayerList);
	}
}