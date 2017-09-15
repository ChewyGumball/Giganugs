#pragma once
#include <vector>

namespace Giganugs::Sprites {
	class SpriteAtlas;

	class SpriteAnimation
	{
		float secondsPerFrame;

	public:
		std::vector<uint32_t> frames;

		SpriteAnimation(std::string_view filename, SpriteAtlas* atlas);
		~SpriteAnimation();
	};
}
