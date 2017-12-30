#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace Giganugs::Sprites {
	class SpriteAtlas;
}

namespace Giganugs::Game::Data {
	struct Recipe;

	struct MachineData
	{
		const uint32_t id;
		const std::string name;

		const Sprites::SpriteAtlas* atlas;
		const uint32_t atlasIndex;

		const std::vector<const Recipe*> recipies;

		MachineData();
		MachineData(uint32_t id, const Sprites::SpriteAtlas* atlas, uint32_t atlasIndex);
	};
}

