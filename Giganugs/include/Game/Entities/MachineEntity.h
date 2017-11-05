#pragma once

#include "Game/Entities/Entity.h"
namespace Giganugs::Game::Entities {

	enum Counters {
		EmptySink,
		FullSink,
		EmptyCuttingBoard,
		ChickenCuttingBoard,
		OvenOpen,
		OvenClosed
	};

	class MachineEntity : public Entity
	{
	private:

	public:
		MachineEntity(Counters type);
		~MachineEntity();
	};
}
