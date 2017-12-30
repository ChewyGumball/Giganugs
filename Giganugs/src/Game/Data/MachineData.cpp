#include "Game/Data/MachineData.h"

namespace Giganugs::Game::Data {
	MachineData::MachineData() 
		:id(id), name(""), atlas(nullptr), atlasIndex(0)
	{
	}
	MachineData::MachineData(uint32_t id, const Sprites::SpriteAtlas * atlas, uint32_t atlasIndex)
		:id(id), name(""), atlas(atlas), atlasIndex(atlasIndex)
	{
	}
}