#pragma once
#include <cstdint>

namespace Giganugs::Game {
	struct Item
	{
		const uint32_t id;
		uint32_t count;

		Item();
		Item(uint32_t id, uint32_t count);
		~Item();
	};
}
