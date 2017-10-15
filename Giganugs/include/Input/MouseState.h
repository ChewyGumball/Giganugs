#pragma once
#include <unordered_map>

#include "lib/glm/vec2.hpp"

#include "Input/InputState.h"

namespace Giganugs::Input
{
	class MouseState
	{
	private:
		glm::vec2 mousePosition;
		glm::vec2 mouseDeltaPosition;
		std::unordered_map<MouseButton, InputState> state;
		std::unordered_map<MouseButton, InputState> stateChangesThisFrame;

		int wheelTicks;
	public:
		MouseState();
		~MouseState();

		glm::vec2 position() const;
		glm::vec2 deltaPosition() const;
		int wheel() const;

		void setPosition(int x, int y);
		void setPositionDelta(int deltaX, int deltaY);
		void setWheelTicks(int ticks);
		void setWheelTicksDelta(int deltaTicks);
		void setButtonState(MouseButton button, InputState inputState);
		void clear();
		void newFrame();

		const InputState& operator[](MouseButton button) const;
		bool changedThisFrame(MouseButton button) const;
	};
}
