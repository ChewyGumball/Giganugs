#include "Sprites/SpriteBatch.h"
#include "Sprites/SpriteAtlas.h"

namespace Giganugs::Sprites {
	SpriteBatch::SpriteBatch(SpriteAtlas* atlas, std::vector<SpriteInstanceData> instances)
		:atlas(atlas), instances(instances)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}
}
