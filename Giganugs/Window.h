#pragma once
#include <string>
#include <windows.h>

namespace Giganugs::Graphics {

	class Window
	{

	private:
		HINSTANCE instance;
		HWND windowHandle;
		std::wstring applicationName;

		int width;
		int height;


	public:
		Window(int width, int height, const std::wstring& windowName, int showState = SW_SHOW);
		~Window();

		LRESULT MessagePump(UINT message, WPARAM wparam, LPARAM lparam);

		const HWND handle() const;

		int Width() const;
		int Height() const;
	};
}
