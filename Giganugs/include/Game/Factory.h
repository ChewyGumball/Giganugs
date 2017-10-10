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
		Sprites::SpriteMap machineMap;

		std::vector<Entities::ItemEntity> items;
		std::vector<Entities::MachineEntity> machines;

	public:
		Factory(Sprites::SpriteMap floor, Sprites::SpriteMap machine);
		~Factory();

		void Update(std::chrono::duration<float> timeDelta);
		void Draw(Graphics::Renderer& renderer, const Graphics::Camera& camera);
	};
}

