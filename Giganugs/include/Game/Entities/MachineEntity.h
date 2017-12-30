#pragma once

#include "Game/Entities/Entity.h"
#include "Game/Item.h"
#include "Input/Clock.h"
#include "Input/Timer.h"

namespace Giganugs::Game::Data {
	struct MachineData;
	struct Recipe;
}

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
		Item m_inventory;
		bool currentlyProcessing;
		Input::Timer processingTimer;

		const Data::Recipe* currentRecipe;

	public:
		const Data::MachineData* data;

		MachineEntity(const Data::MachineData* machineData, glm::vec2 position, glm::vec2 bounds, const Input::Clock* clock);
		~MachineEntity();

		bool empty() const;
		Item inventory() const;

		float processingPercentage() const;
		void startProcessing();

		void Update(std::chrono::duration<float> timeDelta, Context& context) override;
	};
}
