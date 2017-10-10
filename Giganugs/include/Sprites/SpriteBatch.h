#pragma once
#include <vector>

#include "Sprites/SpriteAtlasPart.h"

namespace Giganugs::Sprites {
	class SpriteAtlas;

	class SpriteBatch
	{
	public:
		const SpriteAtlas* atlas;
		const std::vector<SpriteInstanceData> instances;

		SpriteBatch(SpriteAtlas* atlas, std::vector<SpriteInstanceData> instances);
		~SpriteBatch();
	};
}
