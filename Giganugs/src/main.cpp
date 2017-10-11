#include <windows.h>
#include <DirectXMath.h>

#include <chrono>

#include "Graphics/Window.h"
#include "Graphics/Renderer.h"
#include "Graphics/Camera.h"

#include "Sprites/SpriteMap.h"
#include "Sprites/SpriteAtlas.h"
#include "Sprites/SpriteAnimation.h"

#include "Resources/Catalogs/TextureCatalog.h"
#include "Resources/Catalogs/SpriteAtlasCatalog.h"

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

	Giganugs::Sprites::SpriteAtlas* dogs = spriteAtlases.locate("dogs.atlas");
	Giganugs::Sprites::SpriteAtlas* floors = spriteAtlases.locate("wood_floors.atlas");

	Giganugs::Sprites::SpriteAnimation brownDown("resources/sprites/animations/dog_brown_walk_down.anim", dogs);
	Giganugs::Sprites::SpriteAnimation greyDown("resources/sprites/animations/dog_grey_walk_up.anim", dogs);
	Giganugs::Sprites::SpriteAnimation tanRight("resources/sprites/animations/dog_tan_walk_right.anim", dogs);
	Giganugs::Sprites::SpriteAnimation shiftLeft("resources/sprites/animations/dog_shirt_walk_left.anim", dogs);

	Giganugs::Graphics::Camera camera(0.f, 400.f, 0.f, 400.f, 0.f, 1.f);
	renderer.setCamera(camera);

	Giganugs::Sprites::SpriteMap map(100, 100, 32, floors);
	for (int x = 0; x < 100; x++) {
		for (int y = 0; y < 100; y++) {
			map.set(x, y, (x / 10) + (y / 10));
		}
	}


	uint32_t timer = 0;
	uint32_t currentFrame = 0;

	std::vector<Giganugs::Sprites::SpriteInstanceData> parts;
	parts.push_back({ 0, 0, 32, 32, dogs->part(brownDown.frames[currentFrame]) });
	parts.push_back({ 32, 32, 32, 32, dogs->part(greyDown.frames[currentFrame]) });
	parts.push_back({ 32, 0, 32, 32, dogs->part(tanRight.frames[currentFrame]) });
	parts.push_back({ 0, 32, 32, 32, dogs->part(shiftLeft.frames[currentFrame]) });
	
	std::chrono::high_resolution_clock clock;
	
	auto previousTime = clock.now();

	float speed = 128;

	MSG message;
	bool running = true;
	while (running) {
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);

			running = message.message != WM_QUIT;
		}
		else {
			auto currentTime = clock.now();
			std::chrono::duration<float> timeDelta = currentTime - previousTime;
			previousTime = currentTime;

			timer++;

			Util::File::MonitorFiles();

			bool updateBatch = false;
			if (timer % 1000 == 0) {
				currentFrame = (currentFrame + 1) % brownDown.frames.size();
				parts[0].atlasData = dogs->part(brownDown.frames[currentFrame]);
				parts[1].atlasData = dogs->part(greyDown.frames[currentFrame]);
				parts[2].atlasData = dogs->part(tanRight.frames[currentFrame]);
				parts[3].atlasData = dogs->part(shiftLeft.frames[currentFrame]);
			}

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

			renderer.Clear();

			renderer.setCamera(camera);

			renderer.Draw(map.spritesInView(camera));
			renderer.Draw({ dogs, parts });

			renderer.Swap();
		}
	}

	return static_cast<int>(message.wParam);
}