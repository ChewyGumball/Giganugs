#pragma once
#include <chrono>
#include <string>
#include <vector>

#include "Game/Item.h"

namespace Giganugs::Game::Data {
	struct Recipe
	{
		const uint32_t id;
		const std::string name;

		const std::vector<Item> ingredients;
		const std::vector<Item> results;

		const std::chrono::duration<float> baseProcessingTime;
	};
}
