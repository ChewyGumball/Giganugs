#pragma once

namespace Giganugs::Input {
	class MouseState;
	class KeyboardState;
	class Clock;
}

namespace Giganugs::Game {
	struct Context
	{
		const Input::MouseState* mouse;
		const Input::KeyboardState* keyboard;
		const Input::Clock* gameClock;
		const Input::Clock* systemClock;
	};
}
