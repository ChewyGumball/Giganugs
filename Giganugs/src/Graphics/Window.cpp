#include <unordered_map>

#include "Graphics/Window.h"

namespace {
	std::wstring windowClassName = L"win32app";

	std::unordered_map<HWND, Giganugs::Graphics::Window*> messagePumps;

	LRESULT CALLBACK MainMessagePump(HWND windowHandle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			auto window = messagePumps.find(windowHandle);
			if (window == messagePumps.end()) {
				return DefWindowProc(windowHandle, message, wparam, lparam);
			}
			else {
				return window->second->MessagePump(message, wparam, lparam);
			}
		}

		return 0;
	}
}

namespace Giganugs::Graphics {


	LRESULT Window::MessagePump(UINT message, WPARAM wparam, LPARAM lparam)
	{
		return DefWindowProc(windowHandle, message, wparam, lparam);
	}

	const HWND Window::handle() const
	{
		return windowHandle;
	}

	int Window::Width() const
	{
		return width;
	}

	int Window::Height() const
	{
		return height;
	}

	Window::Window(int width, int height, const std::wstring& windowName, int showState)
		: instance(GetModuleHandle(nullptr)), applicationName(windowName), width(width), height(height)
	{
		WNDCLASSEX windowClass;

		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = MainMessagePump;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = instance;
		windowClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
		windowClass.hIconSm = windowClass.hIcon;
		windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		windowClass.lpszMenuName = nullptr;
		windowClass.lpszClassName = windowClassName.c_str();
		windowClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));

		if (!RegisterClassEx(&windowClass)) {
			MessageBox(nullptr, L"Failed to create window class!", L"ERROR", 0);
			return;
		}

		RECT windowRect = { 0, 0, width, height };
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

		windowHandle = CreateWindowEx(NULL, 
									  windowClassName.c_str(), 
									  applicationName.c_str(), 
									  WS_OVERLAPPEDWINDOW, 
									  CW_USEDEFAULT, 
									  CW_USEDEFAULT, 
									  windowRect.right - windowRect.left, 
									  windowRect.bottom - windowRect.top,
									  nullptr, 
									  nullptr, 
									  instance, 
									  nullptr);

		if (!windowHandle) {
			MessageBox(nullptr, L"Failed to create window!", L"ERROR", 0);
			return;
		}

		messagePumps[windowHandle] = this;

		ShowWindow(windowHandle, showState);
	}

	Window::~Window()
	{
	}
}
