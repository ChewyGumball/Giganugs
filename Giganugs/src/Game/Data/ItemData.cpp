#include "Game/Data/ItemData.h"

#include "Sprites/SpriteAtlas.h"


namespace Giganugs::Game {
	ItemData::ItemData(uint32_t id, Sprites::SpriteAtlas* atlas, uint32_t atlasIndex, std::string name)
		:id(id), atlas(atlas), atlasIndex(atlasIndex), name(name)
	{
	}


	ItemData::~ItemData()
	{
	}
}
