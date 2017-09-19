#include "Sprites/SpriteAnimation.h"

#include "Sprites/SpriteAtlas.h"

#include "Util/FileUtils.h"
#include "Util/StringUtils.h"

namespace Giganugs::Sprites {
	SpriteAnimation::SpriteAnimation(std::string_view filename, SpriteAtlas* atlas)
	{
		std::string contents = Util::File::ReadWholeFile(filename);
		std::vector<std::string_view> fileLines = Util::String::Split(contents, '\n');

		secondsPerFrame = Util::String::svtof(fileLines[0]);

		frames.reserve(fileLines.size() - 1);
		for (int32_t i = 1; i < fileLines.size(); i++) {
			frames.push_back(atlas->indexOf(std::string(fileLines[i])));
		}
	}


	SpriteAnimation::~SpriteAnimation()
	{
	}
}
