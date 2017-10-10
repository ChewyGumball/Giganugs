#pragma once
#include <cstdint>
#include <string>

namespace Giganugs::Sprites {
	class SpriteAtlas;
}

namespace Giganugs::Game {
	class ItemData
	{
	public:
		const uint32_t id;
		const Sprites::SpriteAtlas* atlas;
		const uint32_t atlasIndex;

		const std::string name;

		ItemData(uint32_t id, Sprites::SpriteAtlas* atlas, uint32_t atlasIndex, std::string name);
		~ItemData();
	};
}
