#include "Sprites/SpriteBatch.h"
#include "Sprites/SpriteAtlas.h"

namespace Giganugs::Sprites {
	SpriteBatch::SpriteBatch(SpriteAtlas* atlas)
		:atlas(atlas)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::clear()
	{
		instances.clear();
	}
	void SpriteBatch::add(SpriteInstanceData instance)
	{
		instances.push_back(instance);
	}
	const std::vector<SpriteInstanceData>& SpriteBatch::instanceData() const
	{
		return instances;
	}
}
