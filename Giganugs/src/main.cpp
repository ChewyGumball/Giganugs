#include <windows.h>
#include <DirectXMath.h>

#include "Graphics/Window.h"
#include "Graphics/Renderer.h"

#include "Sprites/SpriteAtlas.h"
#include "Sprites/SpriteAnimation.h"

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if(!DirectX::XMVerifyCPUSupport()) {
		MessageBox(nullptr, L"Direct X Math is not supported on this platform!", L"ERROR", 0);
		return 1;
	}

	Giganugs::Graphics::Window window(800, 800, L"HELPS!", nCmdShow);
	Giganugs::Graphics::Renderer renderer(&window);

	Giganugs::Sprites::SpriteAtlas atlas(0, "resources/sprites/atlases/sprites.atlas", renderer.getDevice());
	Giganugs::Sprites::SpriteAnimation greyUp("resources/sprites/animations/dog_grey_walk_up.anim", &atlas);

	renderer.setTexture(atlas.texture());

	uint32_t timer = 0;
	uint32_t currentFrame = 0;

	std::vector<Giganugs::Sprites::SpriteInstanceData> parts;
	parts.push_back({ 0, 0, 0, atlas.part(greyUp.frames[currentFrame]) });
	parts.push_back({ -1, -1, 0, atlas.part(3) });
	parts.push_back({ -1, 0, 0, atlas.part(14) });
	parts.push_back({ 0, -1, 0, atlas.part(24) });

	renderer.setBatch(parts);


	MSG message;
	bool running = true;
	while (running) {
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);

			running = message.message != WM_QUIT;
		}
		else {
			timer++;
			if (timer % 100 == 0) {
				currentFrame = (currentFrame + 1) % greyUp.frames.size();
				parts[0].atlasData = atlas.part(greyUp.frames[currentFrame]);
				renderer.setBatch(parts);
			}
			renderer.Clear();
			renderer.Draw(parts.size());
			renderer.Swap();
		}
	}

	return static_cast<int>(message.wParam);
}