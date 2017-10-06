#include "Sprites/SpriteMap.h"
#include <algorithm>

namespace Giganugs::Sprites {

	SpriteMap::SpriteMap(int width, int height, SpriteAtlas* atlas)
		:m_width(width), m_height(height), atlas(atlas), sprites(width * height)
	{
	}


	SpriteMap::~SpriteMap()
	{
	}

	void SpriteMap::set(int32_t x, int32_t y, uint32_t spriteIndex)
	{
		sprites[x * m_width + y] = { (float)x * 32, (float)y * 32, (float)32, (float)32, atlas->part(spriteIndex) };
	}


	std::vector<SpriteInstanceData> SpriteMap::spritesInView(float viewX, float viewY, float viewWidth, float viewHeight)
	{
		uint32_t startX = static_cast<uint32_t>(std::clamp(std::floorf(viewX), 0.f, static_cast<float>(m_width)));
		uint32_t startY = static_cast<uint32_t>(std::clamp(std::floorf(viewY), 0.f, static_cast<float>(m_height)));
		uint32_t endX = static_cast<uint32_t>(std::clamp(std::ceilf(viewWidth), 0.f, static_cast<float>(m_width)));
		uint32_t endY = static_cast<uint32_t>(std::clamp(std::ceilf(viewHeight), 0.f, static_cast<float>(m_height)));

		std::vector<SpriteInstanceData> visibleSprites;

		for (uint32_t row = startX; row < endX; row++) {
			for (uint32_t column = startY; column < endY ; column++) {
				visibleSprites.push_back(sprites[row * m_width + column]);
			}
		}
		
		return visibleSprites;
	}
	int SpriteMap::width() const
	{
		return m_width;
	}
	int SpriteMap::height() const
	{
		return m_height;
	}
}
