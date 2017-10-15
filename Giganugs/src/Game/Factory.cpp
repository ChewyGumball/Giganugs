#include "Game/Factory.h"

#include "Graphics/Camera.h"


namespace Giganugs::Game {

	Factory::Factory(Sprites::SpriteMap floor, Sprites::SpriteMap machine)
		:floorMap(floor), machineMap(machine)
	{
	}


	Factory::~Factory()
	{
	}

	void Factory::Update(std::chrono::duration<float> timeDelta)
	{
	}

	void Factory::Draw(Giganugs::Graphics::Renderer& renderer, const Giganugs::Graphics::Camera & camera)
	{
		renderer.Draw(floorMap.spritesInView(camera));
		renderer.Draw(machineMap.spritesInView(camera));
	}
	void Factory::setMachine(int32_t x, int32_t y, int32_t spriteIndex)
	{
		machineMap.setAtPixelCoordinates(x, y, spriteIndex);
	}
}
