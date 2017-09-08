#include "Graphics/Window.h"
#include "Graphics/Renderer.h"
#include <windows.h>
#include <DirectXMath.h>

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if(!DirectX::XMVerifyCPUSupport()) {
		MessageBox(nullptr, L"Direct X Math is not supported on this platform!", L"ERROR", 0);
		return 1;
	}

	Giganugs::Graphics::Window window(250, 250, L"HELPS!", nCmdShow);
	Giganugs::Graphics::Renderer renderer(&window);

	MSG message;
	bool running = true;
	while (running) {
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);

			running = message.message != WM_QUIT;
		}
		else {
			renderer.Clear();
			renderer.Draw();
			renderer.Swap();
		}
	}

	return static_cast<int>(message.wParam);
}