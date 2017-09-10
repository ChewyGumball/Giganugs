#pragma once
#include <cstdint>

namespace Giganugs::Sprites {
	struct Sprite
	{
		float x;
		float y;
		float width; 
		float height;

		uint8_t layer;

		uint32_t atlasID;
		uint32_t atlasIndex;

		bool inside(float minX, float minY, float maxX, float maxY);
	};
}
