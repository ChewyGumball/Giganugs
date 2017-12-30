#include <windows.h>
#include <DirectXMath.h>

#include <chrono>
#include <vector>

#include "Graphics/Window.h"
#include "Graphics/Renderer.h"
#include "Graphics/Camera.h"

#include "Sprites/SpriteMap.h"
#include "Sprites/SpriteAtlas.h"
#include "Sprites/SpriteAnimation.h"
#include "Sprites/SpriteAnimator.h"

#include "Resources/Catalogs/TextureCatalog.h"
#include "Resources/Catalogs/SpriteAtlasCatalog.h"
#include "Resources/Catalogs/SpriteAnimationCatalog.h"

#include "Input/Clock.h"
#include "Input/Timer.h"

#include "Game/Context.h"
#include "Game/Factory.h"

#include "Game/Data/MachineData.h"
#include "Game/Data/Recipe.h"

#include "Game/Entities/MachineEntity.h"
#include "Game/Entities/PlayerEntity.h"

#include "Util/FileUtils.h"


int CALLBACK WinMain(HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if(!DirectX::XMVerifyCPUSupport()) {
		MessageBox(nullptr, L"Direct X Math is not supported on this platform!", L"ERROR", 0);
		return 1;
	}

	Giganugs::Graphics::Window window(400, 400, L"HELPS!", nCmdShow);
	Giganugs::Graphics::Renderer renderer(&window);

	Giganugs::Resources::TextureCatalog textures({ "resources/sprites/images" }, renderer.getDevice());
	Giganugs::Resources::SpriteAtlasCatalog spriteAtlases({ "resources/sprites/atlases" }, &textures);
	Giganugs::Resources::SpriteAnimationCatalog spriteAnimations({ "resources/sprites/animations" }, &spriteAtlases);

	Giganugs::Sprites::SpriteAtlas* dogs = spriteAtlases.locate("dogs.atlas");
	Giganugs::Sprites::SpriteAtlas* counters = spriteAtlases.locate("counters.atlas");

	Giganugs::Graphics::Camera camera(0.f, 400.f, 0.f, 400.f, 0.f, 1.f);
	renderer.setCamera(camera);

	Giganugs::Sprites::SpriteMap map(100, 100, 32, spriteAtlases.locate("wood_floors.atlas"));
	for (int x = 0; x < 100; x++) {
		for (int y = 0; y < 100; y++) {
			map.setAtTileCoordinates(x, y, (x / 10) + (y / 10));
		}
	}

	Giganugs::Input::Clock gameClock;
	Giganugs::Input::Clock systemClock;

	std::vector<Giganugs::Game::Data::MachineData> machineDatas;
	for (int i = 0; i < 64; i++) {
		machineDatas.push_back(Giganugs::Game::Data::MachineData( i, counters, i));
	}

	std::vector<Giganugs::Game::Entities::MachineEntity*> machines;

	Giganugs::Game::Factory factory(map);
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			Giganugs::Game::Entities::MachineEntity* machine = new Giganugs::Game::Entities::MachineEntity(&machineDatas.at(x * 8 + y), glm::vec2((x + 3) * map.tileSize(), (y + 3) * map.tileSize()), glm::vec2(map.tileSize(), map.tileSize()), &gameClock);
			machines.push_back(machine);
			factory.add(machine);
		}
	}	

	Giganugs::Input::Timer timer(&gameClock);

	Giganugs::Game::Entities::PlayerEntity player("dog_grey", &spriteAnimations, &gameClock, Giganugs::Right);
	player.move(Giganugs::Right, 32);
	player.move(Giganugs::Up, 32);


	Giganugs::Game::Context context{ &window.mouse(), &window.keyboard(), &gameClock, &systemClock };	

	float speed = 128;

	uint32_t counterIndex = 0;

	std::vector<Giganugs::Game::Entities::Entity*> entities; 
	entities.push_back(&player);


	Giganugs::Sprites::SpriteBatch playerBatch(dogs);
	Giganugs::Sprites::SpriteInstanceData playerSprite = { player.position().x, player.position().y, 32, 32, dogs->part(player.currentAnimator().currentFrameIndex()) };


	MSG message;
	bool running = true;
	while (running) {
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);

			running = message.message != WM_QUIT;
		}
		else {
			gameClock.tick();
			systemClock.tick();

			auto& timeDelta = context.gameClock->deltaTickSeconds();

			Util::File::MonitorFiles();

			for (auto entity : entities) {
				entity->Update(timeDelta, context);
			}


			playerSprite.atlasData = dogs->part(player.currentAnimator().currentFrameIndex());
			playerSprite.x = player.position().x;
			playerSprite.y = player.position().y;
			playerBatch.clear();
			playerBatch.add(playerSprite);

			if (window.keyboard()[Giganugs::Input::Key::D] == Giganugs::Input::InputState::Pressed) {
				camera.move(glm::vec2(speed * timeDelta.count(), 0.f));
				//parts[2].x += speed * timeDelta.count();
			}
			if (window.keyboard()[Giganugs::Input::Key::W] == Giganugs::Input::InputState::Pressed) {
				camera.move(glm::vec2(0.f, speed * timeDelta.count()));
				//parts[1].y += speed * timeDelta.count();
			}
			if (window.keyboard()[Giganugs::Input::Key::A] == Giganugs::Input::InputState::Pressed) {
				camera.move(glm::vec2(-speed * timeDelta.count(),0.f));
			}
			if (window.keyboard()[Giganugs::Input::Key::S] == Giganugs::Input::InputState::Pressed) {
				camera.move(glm::vec2(0.f, -speed * timeDelta.count()));
			}
			
			if (window.keyboard().stateChangeThisFrame(Giganugs::Input::Key::P) == Giganugs::Input::InputState::Pressed) {
				gameClock.pause();
			}
			if (window.keyboard().stateChangeThisFrame(Giganugs::Input::Key::U) == Giganugs::Input::InputState::Pressed) {
				gameClock.resume();
			}

			renderer.Clear();
			renderer.setCamera(camera);

			factory.Draw(renderer, camera);
			renderer.Draw(playerBatch);

			renderer.Swap();

			window.newInputFrame();
		}
	}

	return static_cast<int>(message.wParam);
}