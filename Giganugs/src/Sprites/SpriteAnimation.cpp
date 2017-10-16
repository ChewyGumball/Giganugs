#include "Sprites/SpriteAnimation.h"

#include "Sprites/SpriteAtlas.h"

#include "Resources/Catalogs/SpriteAtlasCatalog.h"

#include "Util/FileUtils.h"
#include "Util/StringUtils.h"

namespace Giganugs::Sprites {
	SpriteAnimation::SpriteAnimation(uint32_t ID, std::string_view filename, Resources::SpriteAtlasCatalog* atlasCatalog)
		:Resource(ID)
	{
		reload(filename, atlasCatalog);
	}


	SpriteAnimation::~SpriteAnimation()
	{
	}
	float SpriteAnimation::secondsPerFrame() const
	{
		return m_secondsPerFrame;
	}
	bool SpriteAnimation::reload(const std::string_view & filename, Resources::SpriteAtlasCatalog * atlasCatalog)
	{
		std::string contents = Util::File::ReadWholeFile(filename);
		std::vector<std::string_view> fileLines = Util::String::Split(contents, '\n');

		auto firstLine = Util::String::Split(fileLines[0], ' ');

		auto* atlas = atlasCatalog->locate(std::string(firstLine[0]));

		m_secondsPerFrame = Util::String::svtof(firstLine[1]);

		frames.reserve(fileLines.size() - 1);
		for (int32_t i = 1; i < fileLines.size(); i++) {
			frames.push_back(atlas->indexOf(std::string(fileLines[i])));
		}

		return true;
	}
}
