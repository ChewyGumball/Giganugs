#include <unordered_map>

#include "Window.h"
namespace {
	std::wstring windowClassName = L"win32app";

	std::unordered_map<HWND, Window*> messagePumps;

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

LRESULT Window::MessagePump(UINT message, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(windowHandle, message, wparam, lparam);
}

Window::Window(int width, int height, const std::wstring& windowName, int showState) 
	: instance(GetModuleHandle(nullptr)), applicationName(windowName)
{
	WNDCLASSEX windowClass;

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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

	windowHandle = CreateWindowEx(WS_EX_APPWINDOW, windowClassName.c_str(), applicationName.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, instance, nullptr);

	if (!windowHandle) {
		MessageBox(nullptr, L"Failed to create window!", L"ERROR", 0);
		return;
	}

	ShowWindow(windowHandle, showState);
}

Window::~Window()
{
}
