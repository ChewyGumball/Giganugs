#pragma once
#include <string>
#include <windows.h>

#include "Input/KeyboardState.h"
#include "Input/MouseState.h"

namespace Giganugs::Graphics {

	class Window
	{

	private:
		HINSTANCE instance;
		HWND windowHandle;
		std::wstring applicationName;

		int width;
		int height;

		Input::KeyboardState keyboardState;
		Input::MouseState mouseState;

	public:
		Window(int width, int height, const std::wstring& windowName, int showState = SW_SHOW);
		~Window();

		LRESULT MessagePump(UINT message, WPARAM wparam, LPARAM lparam);

		const HWND handle() const;

		int Width() const;
		int Height() const;

		const Input::KeyboardState& keyboard() const;
		const Input::MouseState& mouse() const;

		void newInputFrame();
	};
}
