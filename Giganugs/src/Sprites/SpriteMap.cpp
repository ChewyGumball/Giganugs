#include "Sprites/SpriteMap.h"
#include <algorithm>

#include "Util/FileUtils.h"
#include "Util/StringUtils.h"

#include "Graphics/Camera.h"

using Microsoft::WRL::ComPtr;

namespace Giganugs::Sprites {

	SpriteMap::SpriteMap(uint32_t width, uint32_t height, uint32_t tilePixelSize, SpriteAtlas* atlas)
		:m_width(width), m_height(height), tilePixelSize(tilePixelSize), atlas(atlas), sprites(width * height)
	{
	}

	SpriteMap::SpriteMap(std::string_view filename, ComPtr<ID3D11Device> device)
	{
		std::string contents = Util::File::ReadWholeFile(filename);
		std::vector<std::string_view> fileLines = Util::String::Split(contents, '\n');

		auto firstLine = Util::String::Split(fileLines[0], ' ');

		std::string atlasFilename = "resources/sprites/atlases/" + std::string(firstLine[0]);

		//atlas =
		//Should sprite map own the atlas? no!
	}


	SpriteMap::~SpriteMap()
	{
	}

	void SpriteMap::setAtTileCoordinates(int32_t x, int32_t y, uint32_t spriteIndex)
	{
		auto& instance = sprites[x * m_width + y];
		instance.x = (float)x * tilePixelSize;
		instance.y = (float)y * tilePixelSize;
		instance.width = (float)tilePixelSize;
		instance.height = (float)tilePixelSize;
		instance.atlasData = atlas->part(spriteIndex);
	}

	void SpriteMap::setAtPixelCoordinates(int32_t x, int32_t y, uint32_t spriteIndex)
	{
		setAtTileCoordinates(x / tilePixelSize, y / tilePixelSize, spriteIndex);
	}

	void SpriteMap::clearAtTileCoordinates(int32_t x, int32_t y)
	{
		auto& instance = sprites[x * m_width + y];
		instance.width = 0; // HACK: spritesInView checks for width == 0 to decide if this sprite should be drawn
	}

	void SpriteMap::clearAtPixelCoordinates(int32_t x, int32_t y)
	{
		clearAtTileCoordinates(x / tilePixelSize, y / tilePixelSize);
	}


	SpriteBatch SpriteMap::spritesInView(const Graphics::Camera & camera)
	{
		glm::vec2 cameraPosition = camera.position() / glm::vec3(static_cast<float>(tilePixelSize));
		return spritesInView(cameraPosition.x, cameraPosition.y, camera.width() / tilePixelSize / camera.zoom(), camera.height() / tilePixelSize / camera.zoom());
	}

	SpriteBatch SpriteMap::spritesInView(float viewX, float viewY, float viewWidth, float viewHeight)
	{
		uint32_t startX = static_cast<uint32_t>(std::clamp(std::floorf(viewX), 0.f, static_cast<float>(m_width)));
		uint32_t startY = static_cast<uint32_t>(std::clamp(std::floorf(viewY), 0.f, static_cast<float>(m_height)));
		uint32_t endX = static_cast<uint32_t>(std::clamp(std::ceilf(viewX + viewWidth), 0.f, static_cast<float>(m_width)));
		uint32_t endY = static_cast<uint32_t>(std::clamp(std::ceilf(viewY + viewHeight), 0.f, static_cast<float>(m_height)));

		SpriteBatch batch(atlas);

		for (uint32_t row = startX; row < endX; row++) {
			for (uint32_t column = startY; column < endY ; column++) {
				auto& spriteInstance = sprites[row * m_width + column];
				if (spriteInstance.width != 0) {
					batch.add(spriteInstance);
				}
			}
		}
		
		return batch;
	}
	uint32_t SpriteMap::width() const
	{
		return m_width;
	}
	uint32_t SpriteMap::height() const
	{
		return m_height;
	}
	uint32_t SpriteMap::tileSize() const
	{
		return tilePixelSize;
	}
}
