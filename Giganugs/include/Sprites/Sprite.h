#pragma once
#include <cstdint>

namespace Giganugs::Sprites {
	struct Sprite
	{
		float width; 
		float height;

		uint32_t atlasID;
		uint32_t atlasIndex;

		bool inside(float minX, float minY, float maxX, float maxY);
	};
}
