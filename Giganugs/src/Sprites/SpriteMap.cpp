#include "Sprites/SpriteMap.h"
#include <algorithm>

namespace Giganugs::Sprites {

	SpriteMap::SpriteMap(int width, int height)
		:width(width), height(height), sprites(width * height)
	{
	}


	SpriteMap::~SpriteMap()
	{
	}

	void SpriteMap::set(Sprite sprite)
	{
		int x = static_cast<int>(std::floorf(sprite.x));
		int y = static_cast<int>(std::floorf(sprite.y));
		sprites[x * width + y] = sprite;
	}


	std::vector<Sprite*> SpriteMap::spritesInView(float viewX, float viewY, float viewWidth, float viewHeight)
	{
		uint32_t startX = static_cast<uint32_t>(std::floorf(viewX));
		uint32_t startY = static_cast<uint32_t>(std::floorf(viewY));
		uint32_t endX = static_cast<uint32_t>(std::ceilf(viewWidth));
		uint32_t endY = static_cast<uint32_t>(std::ceilf(viewHeight));

		std::vector<Sprite*> visibleSprites;

		for (uint32_t row = startX; row < endX; row++) {
			for (uint32_t column = startY; column < endY ; column++) {
				visibleSprites.push_back(&sprites[row * width + column]);
			}
		}
		
		return visibleSprites;
	}
}
