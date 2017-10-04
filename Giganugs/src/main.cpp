#include <windows.h>
#include <DirectXMath.h>

#include <chrono>

#include "Graphics/Window.h"
#include "Graphics/Renderer.h"

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

	Giganugs::Sprites::SpriteAtlas atlas(0, "resources/sprites/atlases/dogs.atlas", renderer.getDevice());
	Giganugs::Sprites::SpriteAtlas floors(0, "resources/sprites/atlases/wood_floors.atlas", renderer.getDevice());

	Giganugs::Sprites::SpriteAnimation brownDown("resources/sprites/animations/dog_brown_walk_down.anim", &atlas);
	Giganugs::Sprites::SpriteAnimation greyDown("resources/sprites/animations/dog_grey_walk_up.anim", &atlas);
	Giganugs::Sprites::SpriteAnimation tanRight("resources/sprites/animations/dog_tan_walk_right.anim", &atlas);
	Giganugs::Sprites::SpriteAnimation shiftLeft("resources/sprites/animations/dog_shirt_walk_left.anim", &atlas);

	Giganugs::Sprites::SpriteMap map(4, 4, &floors);
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			map.set(x, y, 0);
		}
	}


	uint32_t timer = 0;
	uint32_t currentFrame = 0;

	std::vector<Giganugs::Sprites::SpriteInstanceData> parts;
	parts.push_back({ 0, 0, 1, 1, atlas.part(brownDown.frames[currentFrame]) });
	parts.push_back({ 1, 1, 1, 1, atlas.part(greyDown.frames[currentFrame]) });
	parts.push_back({ 1, 0, 1, 1, atlas.part(tanRight.frames[currentFrame]) });
	parts.push_back({ 0, 1, 1, 1, atlas.part(shiftLeft.frames[currentFrame]) });

	renderer.setBatch(parts);

	std::chrono::high_resolution_clock clock;
	
	auto previousTime = clock.now();

	float speed = 1.5;

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
				parts[0].atlasData = atlas.part(brownDown.frames[currentFrame]);
				parts[1].atlasData = atlas.part(greyDown.frames[currentFrame]);
				parts[2].atlasData = atlas.part(tanRight.frames[currentFrame]);
				parts[3].atlasData = atlas.part(shiftLeft.frames[currentFrame]);
			}

			if (window.keyboard()[Giganugs::Input::Key::D] == Giganugs::Input::InputState::Pressed) {
				parts[2].x += speed * timeDelta.count();
			}
			if (window.keyboard()[Giganugs::Input::Key::W] == Giganugs::Input::InputState::Pressed) {
				parts[1].y += speed * timeDelta.count();
			}

			renderer.Clear();

			renderer.setTexture(floors.texture());
			auto batch = map.spritesInView(-1, -1, 3, 3);
			renderer.setBatch(batch);
			renderer.Draw(batch.size());

			renderer.setTexture(atlas.texture());
			renderer.setBatch(parts);
			renderer.Draw(parts.size());

			renderer.Swap();
		}
	}

	return static_cast<int>(message.wParam);
}