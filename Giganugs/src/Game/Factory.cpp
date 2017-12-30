#include "Game/Factory.h"

#include <algorithm>
#include <vector>

#include "Game/Data/MachineData.h"

#include "Graphics/Camera.h"

#include "Sprites/SpriteAtlas.h"
#include "Sprites/SpriteBatch.h"


namespace Giganugs::Game {

	Factory::Factory(Sprites::SpriteMap floor)
		:floorMap(floor)
	{
	}


	Factory::~Factory()
	{
	}

	void Factory::Draw(Giganugs::Graphics::Renderer& renderer, const Giganugs::Graphics::Camera & camera)
	{
		renderer.Draw(floorMap.spritesInView(camera));
		std::unordered_map<uint32_t, Sprites::SpriteBatch> batches;

		for (auto machine : machines) {
			const Data::MachineData* data = machine->data;
			uint32_t atlasID = data->atlas->tag.id();
			if (batches.count(atlasID) == 0) {
				batches.emplace(atlasID, Sprites::SpriteBatch(data->atlas));
			}

			glm::vec2 position = machine->position();
			glm::vec2 bounds = machine->bounds();

			batches.find(atlasID)->second.add({ position.x, position.y, bounds.x, bounds.y, data->atlas->part(data->atlasIndex) });
		}

		for (auto& batch : batches) {
			renderer.Draw(batch.second);
		}
	}
	void Factory::add(Entities::MachineEntity * machine)
	{
		machines.push_back(machine);
	}
	void Factory::add(Entities::ItemEntity * item)
	{
		items.push_back(item);
	}
	void Factory::remove(Entities::MachineEntity * machine)
	{
		machines.erase(std::remove(machines.begin(), machines.end(), machine), machines.end());
	}
	void Factory::remove(Entities::ItemEntity * item)
	{
		items.erase(std::remove(items.begin(), items.end(), item), items.end());
	}
}
