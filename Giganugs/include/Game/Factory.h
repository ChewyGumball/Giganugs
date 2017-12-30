#pragma once
#include <chrono>

#include "Graphics/Renderer.h"
#include "Sprites/SpriteMap.h"

#include "Game/Entities/ItemEntity.h"
#include "Game/Entities/MachineEntity.h"

namespace Giganugs::Game {
	class Factory
	{
		Sprites::SpriteMap floorMap;

		std::vector<Entities::ItemEntity*> items;
		std::vector<Entities::MachineEntity*> machines;

	public:
		Factory(Sprites::SpriteMap floor);
		~Factory();

		void Draw(Graphics::Renderer& renderer, const Graphics::Camera& camera);

		void add(Entities::MachineEntity* machine);
		void add(Entities::ItemEntity* item);

		void remove(Entities::MachineEntity* machine);
		void remove(Entities::ItemEntity* item);
	};
}

