#pragma once

#include <vector>
#include "Sprites/SpriteAtlas.h"
#include "Sprites/SpriteAtlasPart.h"

namespace Giganugs::Sprites {
	class SpriteMap
	{
		int m_width;
		int m_height;

		std::vector<SpriteInstanceData> sprites; 

	public:
		SpriteAtlas* atlas;
		SpriteMap(int width, int height, SpriteAtlas* atlas);
		~SpriteMap();

		void set(int32_t x, int32_t y, uint32_t spriteIndex);

		std::vector<SpriteInstanceData> spritesInView(float x, float y, float width, float height);

		int width() const;
		int height() const;
	};
}
