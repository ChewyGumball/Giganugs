#pragma once

#include <vector>
#include <wrl.h>

#include "Sprites/SpriteAtlas.h"
#include "Sprites/SpriteAtlasPart.h"
#include "Sprites/SpriteBatch.h"

namespace Giganugs::Graphics {
	class Camera;
}

namespace Giganugs::Sprites {
	class SpriteMap
	{
		uint32_t m_width;
		uint32_t m_height;
		uint32_t tilePixelSize;
		SpriteAtlas* atlas;

		std::vector<SpriteInstanceData> sprites; 

	public:
		SpriteMap(int width, int height, int tilePixelSize, SpriteAtlas* atlas);
		SpriteMap(std::string_view filename, Microsoft::WRL::ComPtr<ID3D11Device> device);
		~SpriteMap();

		void set(int32_t x, int32_t y, uint32_t spriteIndex);
		void clear(int32_t x, int32_t y);

		SpriteBatch spritesInView(const Graphics::Camera& camera);
		SpriteBatch spritesInView(float x, float y, float width, float height);

		int width() const;
		int height() const;
	};
}
