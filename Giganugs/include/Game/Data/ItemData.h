#pragma once
#include <cstdint>
#include <string>

namespace Giganugs::Sprites {
	class SpriteAtlas;
}

namespace Giganugs::Game::Data {
	struct ItemData
	{
		const uint32_t id;
		const std::string name;

		const Sprites::SpriteAtlas* atlas;
		const uint32_t atlasIndex;
	};
}
