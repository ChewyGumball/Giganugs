#pragma once
#include <unordered_map>

#include "Input/InputState.h"

namespace Giganugs::Input
{
	class KeyboardState
	{
	private:
		std::unordered_map<Key, InputState> state;
		std::unordered_map<Key, InputState> stateChangesThisFrame;
	public:
		KeyboardState();
		~KeyboardState();

		void setKeyState(Key key, InputState inputState);
		void clear();
		void newFrame();
		
		const InputState& operator[](Key key) const;
		InputState stateChangeThisFrame(Key key) const;
	};
}
