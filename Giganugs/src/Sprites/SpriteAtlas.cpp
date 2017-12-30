#include "Sprites/SpriteAtlas.h"


#include "Util/FileUtils.h"
#include "Util/StringUtils.h"


using Microsoft::WRL::ComPtr;

namespace Giganugs::Sprites {
	SpriteAtlas::SpriteAtlas(uint32_t ID, const std::string& filename, Resources::ResourceCatalog<Graphics::Texture>* textureCatalog)
		:Resource(ID)
	{
		reload(filename, textureCatalog);
	}


	SpriteAtlas::~SpriteAtlas()
	{
	}

	int32_t SpriteAtlas::indexOf(const std::string& spriteName) const
	{
		return namesToIndices.at(spriteName);
	}
	SpriteAtlasPart SpriteAtlas::part(uint32_t index) const
	{
		return parts[index];
	}

	uint32_t SpriteAtlas::partCount() const
	{
		return parts.size();
	}

	Graphics::Texture* SpriteAtlas::texture() const
	{
		return m_texture;
	}

	bool SpriteAtlas::reload(const std::string & filename, Resources::ResourceCatalog<Graphics::Texture>* textureCatalog)
	{
		std::string contents = Util::File::ReadWholeFile(filename);
		std::vector<std::string_view> fileLines = Util::String::Split(contents, '\n');

		auto firstLine = Util::String::Split(fileLines[0], ' ');

		m_texture = textureCatalog->locate(std::string(firstLine[0]));

		int imageWidth = Util::String::svtoi(firstLine[1]);
		int imageHeight = Util::String::svtoi(firstLine[2]);

		for (int32_t i = 1; i < fileLines.size(); i++) {
			auto line = Util::String::Split(fileLines[i], ' ');

			if (line.size() > 0) {
				float x = Util::String::svtof(line[1]);
				float y = Util::String::svtof(line[2]);
				float width = Util::String::svtof(line[3]);
				float height = Util::String::svtof(line[4]);

				namesToIndices[std::string(line[0])] = i - 1;
				parts.push_back({ x / imageWidth, y / imageHeight, width / imageWidth, height / imageHeight });
			}
		}

		return true;
	}
}
