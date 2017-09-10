#pragma once
#include <vector>

namespace Giganugs::Sprites {
	class SpriteAtlas;

	class SpriteAnimation
	{
		float secondsPerFrame;
		std::vector<uint32_t> frames;

	public:

		SpriteAnimation(std::string_view filename, SpriteAtlas* atlas);
		~SpriteAnimation();
	};
}
