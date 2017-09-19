#pragma once
#include <unordered_map>

#include "Input/InputState.h"

namespace Giganugs::Input
{
	class KeyboardState
	{
	private:
		std::unordered_map<Key, InputState> state;
		Key mostRecentlyChangedKey;
	public:
		KeyboardState();
		~KeyboardState();

		void setKeyState(Key key, InputState inputState);
		void clear();
		
		const InputState& operator[](Key key) const;
		const Key& keyWithMostRecentStateChange() const;
	};
}
