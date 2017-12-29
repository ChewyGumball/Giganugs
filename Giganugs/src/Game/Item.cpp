#include "Game/Item.h"


namespace Giganugs::Game {

	Item::Item() : id(0), count(0) {}

	Item::Item(uint32_t id, uint32_t count)
		: id(id), count(count)
	{
	}


	Item::~Item()
	{
	}
}
