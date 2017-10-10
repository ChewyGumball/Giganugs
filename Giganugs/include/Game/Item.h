#pragma once
#include <cstdint>

namespace Giganugs::Game {
	class Item
	{
		const uint32_t id;
		uint32_t count;
		Item();
		~Item();
	};
}
