#pragma once
#include <vector>

#include "Sprites/SpriteAtlasPart.h"

namespace Giganugs::Sprites {
	class SpriteAtlas;

	class SpriteBatch
	{
	private:
		std::vector<SpriteInstanceData> instances;
	public:
		const SpriteAtlas* atlas;

		SpriteBatch(SpriteAtlas* atlas);
		~SpriteBatch();

		void clear();
		void add(SpriteInstanceData instance);

		const std::vector<SpriteInstanceData>& instanceData() const;
	};
}
