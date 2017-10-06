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
	
	using Giganugs::Input::MouseButton;
	using Giganugs::Input::InputState;
	using Giganugs::Input::Key;

	void processKeyDown(WPARAM wparam, Giganugs::Input::KeyboardState& keyboard) {
		switch (wparam) {
		case 0x30: // 0
			keyboard.setKeyState(Key::Zero, InputState::Pressed);
			break;
		case 0x41: // a
			keyboard.setKeyState(Key::A, InputState::Pressed);
			break;
		case 0x44: // d
			keyboard.setKeyState(Key::D, InputState::Pressed);
			break;
		case 0x53: // s
			keyboard.setKeyState(Key::S, InputState::Pressed);
			break;
		case 0x57: // w
			keyboard.setKeyState(Key::W, InputState::Pressed);
			break;
		}
	}

	void processKeyUp(WPARAM wparam, Giganugs::Input::KeyboardState& keyboard) {
		switch (wparam) {
		case 0x30: // 0
			keyboard.setKeyState(Key::Zero, InputState::Released);
			break;
		case 0x41: // a
			keyboard.setKeyState(Key::A, InputState::Released);
			break;
		case 0x44: // d
			keyboard.setKeyState(Key::D, InputState::Released);
			break;
		case 0x53: // s
			keyboard.setKeyState(Key::S, InputState::Released);
			break;
		case 0x57: // w
			keyboard.setKeyState(Key::W, InputState::Released);
			break;
		}
	}

	void processMouseButton(WPARAM wparam, Giganugs::Input::MouseState& mouse, Giganugs::Input::InputState state) {
		switch (wparam) {
		case VK_LBUTTON:
			mouse.setButtonState(MouseButton::Left, state);
			break;
		case VK_RBUTTON:
			mouse.setButtonState(MouseButton::Right, state);
			break;
		case VK_MBUTTON:
			mouse.setButtonState(MouseButton::Middle, state);
			break;
		}
	}

	void processMouseMove(LPARAM lparam, Giganugs::Input::MouseState& mouse, int windowHeight) {
		int x = lparam & 0xFFFF;
		int y = windowHeight - ((lparam & 0xFFFF0000) >> 16);
		mouse.setPosition(x, y);
	}

	using Giganugs::Input::Key;
	void processChar(WPARAM wparam, LPARAM lparam, Giganugs::Input::KeyboardState& keyboard) {
		InputState state = (lparam & 0x80000000) == 0 ? InputState::Pressed : InputState::Released;
		switch (wparam) {
		case 0x30:
			keyboard.setKeyState(Key::Zero, state);
			break;
		case 0x44:
			keyboard.setKeyState(Key::D, state);
			break;
		case 0x57:
			keyboard.setKeyState(Key::W, state);
			break;
		}
	}
	
}

namespace Giganugs::Graphics {


	LRESULT Window::MessagePump(UINT message, WPARAM wparam, LPARAM lparam)
	{		
		switch (message) {
		case WM_LBUTTONDOWN:
			processMouseButton(wparam, mouseState, InputState::Pressed);
			break;
		case WM_LBUTTONUP:
			processMouseButton(wparam, mouseState, InputState::Released);
			break;
		case WM_RBUTTONDOWN:
			processMouseButton(wparam, mouseState, InputState::Pressed);
			break;
		case WM_RBUTTONUP:
			processMouseButton(wparam, mouseState, InputState::Released);
			break;
		case WM_MBUTTONDOWN:
			processMouseButton(wparam, mouseState, InputState::Pressed);
			break;
		case WM_MBUTTONUP:
			processMouseButton(wparam, mouseState, InputState::Released);
			break;
		case WM_MOUSEMOVE:
			processMouseMove(lparam, mouseState, height);
			break;
		case WM_KEYDOWN:
			processKeyDown(wparam, keyboardState);
			break;
		case WM_KEYUP:
			processKeyUp(wparam, keyboardState);
			break;
		case WM_CHAR:
			processChar(wparam, lparam, keyboardState);
			break;
		//default:
		}
		
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
	
	const Input::KeyboardState & Window::keyboard() const
	{
		return keyboardState;
	}

	const Input::MouseState & Window::mouse() const
	{
		return mouseState;
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
