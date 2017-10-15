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
		SpriteMap(uint32_t width, uint32_t height, uint32_t tilePixelSize, SpriteAtlas* atlas);
		SpriteMap(std::string_view filename, Microsoft::WRL::ComPtr<ID3D11Device> device);
		~SpriteMap();

		void setAtTileCoordinates(int32_t x, int32_t y, uint32_t spriteIndex);
		void setAtPixelCoordinates(int32_t x, int32_t y, uint32_t spriteIndex);
		void clearAtTileCoordinates(int32_t x, int32_t y); 
		void clearAtPixelCoordinates(int32_t x, int32_t y);

		SpriteBatch spritesInView(const Graphics::Camera& camera);
		SpriteBatch spritesInView(float x, float y, float width, float height);

		uint32_t width() const;
		uint32_t height() const;
		uint32_t tileSize() const;
	};
}
