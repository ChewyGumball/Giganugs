#pragma once

#include <vector>
#include "Sprites/Sprite.h"

namespace Giganugs::Sprites {
	class SpriteMap
	{
		int width;
		int height;

		std::vector<Sprite> sprites; 

	public:
		SpriteMap(int width, int height);
		~SpriteMap();

		void set(Sprite sprite);

		std::vector<Sprite*> spritesInView(float x, float y, float width, float height);
	};
}
