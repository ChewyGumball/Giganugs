#include <windows.h>
#include <DirectXMath.h>

#include <chrono>

#include "Graphics/Window.h"
#include "Graphics/Renderer.h"
#include "Graphics/Camera.h"

#include "Sprites/SpriteMap.h"
#include "Sprites/SpriteAtlas.h"
#include "Sprites/SpriteAnimation.h"

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if(!DirectX::XMVerifyCPUSupport()) {
		MessageBox(nullptr, L"Direct X Math is not supported on this platform!", L"ERROR", 0);
		return 1;
	}

	Giganugs::Graphics::Window window(400, 400, L"HELPS!", nCmdShow);
	Giganugs::Graphics::Renderer renderer(&window);

	Giganugs::Sprites::SpriteAtlas dogs(0, "resources/sprites/atlases/dogs.atlas", renderer.getDevice());
	Giganugs::Sprites::SpriteAtlas floors(0, "resources/sprites/atlases/wood_floors.atlas", renderer.getDevice());

	Giganugs::Sprites::SpriteAnimation brownDown("resources/sprites/animations/dog_brown_walk_down.anim", &dogs);
	Giganugs::Sprites::SpriteAnimation greyDown("resources/sprites/animations/dog_grey_walk_up.anim", &dogs);
	Giganugs::Sprites::SpriteAnimation tanRight("resources/sprites/animations/dog_tan_walk_right.anim", &dogs);
	Giganugs::Sprites::SpriteAnimation shiftLeft("resources/sprites/animations/dog_shirt_walk_left.anim", &dogs);

	Giganugs::Graphics::Camera camera(0.f, 400.f, 0.f, 400.f, 0.f, 1.f);
	//camera.zoom(2.f);
	renderer.setCamera(camera);

	Giganugs::Sprites::SpriteMap map(100, 100, &floors);
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			map.set(x, y, 0);
		}
	}


	uint32_t timer = 0;
	uint32_t currentFrame = 0;

	std::vector<Giganugs::Sprites::SpriteInstanceData> parts;
	parts.push_back({ 0, 0, 32, 32, dogs.part(brownDown.frames[currentFrame]) });
	parts.push_back({ 32, 32, 32, 32, dogs.part(greyDown.frames[currentFrame]) });
	parts.push_back({ 32, 0, 32, 32, dogs.part(tanRight.frames[currentFrame]) });
	parts.push_back({ 0, 32, 32, 32, dogs.part(shiftLeft.frames[currentFrame]) });

	renderer.setBatch(parts);

	std::chrono::high_resolution_clock clock;
	
	auto previousTime = clock.now();

	float speed = 32;

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

			bool updateBatch = false;
			if (timer % 1000 == 0) {
				currentFrame = (currentFrame + 1) % brownDown.frames.size();
				parts[0].atlasData = dogs.part(brownDown.frames[currentFrame]);
				parts[1].atlasData = dogs.part(greyDown.frames[currentFrame]);
				parts[2].atlasData = dogs.part(tanRight.frames[currentFrame]);
				parts[3].atlasData = dogs.part(shiftLeft.frames[currentFrame]);
			}

			if (window.keyboard()[Giganugs::Input::Key::D] == Giganugs::Input::InputState::Pressed) {
				camera.move(glm::vec2(-speed * timeDelta.count(), 0.f));
				//parts[2].x += speed * timeDelta.count();
			}
			if (window.keyboard()[Giganugs::Input::Key::W] == Giganugs::Input::InputState::Pressed) {
				camera.move(glm::vec2(0.f, -speed * timeDelta.count()));
				//parts[1].y += speed * timeDelta.count();
			}
			if (window.keyboard()[Giganugs::Input::Key::A] == Giganugs::Input::InputState::Pressed) {
				camera.move(glm::vec2(speed * timeDelta.count(),0.f));
			}
			if (window.keyboard()[Giganugs::Input::Key::S] == Giganugs::Input::InputState::Pressed) {
				camera.move(glm::vec2(0.f, speed * timeDelta.count()));
			}

			renderer.Clear();

			renderer.setCamera(camera);

			renderer.setTexture(floors.texture());
			auto batch = map.spritesInView(0, 0, 4, 4);
			renderer.setBatch(batch);
			renderer.Draw(batch.size());

			renderer.setTexture(dogs.texture());
			renderer.setBatch(parts);
			renderer.Draw(parts.size());

			renderer.Swap();
		}
	}

	return static_cast<int>(message.wParam);
}