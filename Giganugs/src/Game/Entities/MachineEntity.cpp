#include "Game/Entities/MachineEntity.h"

#include "Game/Data/Recipe.h"


namespace Giganugs::Game::Entities {

	MachineEntity::MachineEntity(const Data::MachineData* machineData, glm::vec2 position, glm::vec2 bounds, const Input::Clock* clock)
		:Entity(position, bounds), m_inventory(0,0), currentlyProcessing(false), processingTimer(clock), data(machineData)
	{
	}


	MachineEntity::~MachineEntity()
	{
	}
	bool MachineEntity::empty() const
	{
		return m_inventory.count == 0;
	}

	Item MachineEntity::inventory() const
	{
		return m_inventory;
	}

	float MachineEntity::processingPercentage() const
	{
		if (currentlyProcessing) {
			return processingTimer.elapsedSeconds() / currentRecipe->baseProcessingTime;
		}
		else {
			return 0;
		}
	}

	void MachineEntity::startProcessing()
	{
		currentlyProcessing = true;
		processingTimer.restart();
	}

	void MachineEntity::Update(std::chrono::duration<float> timeDelta, Context & context)
	{
		if (currentlyProcessing && processingTimer.elapsedSeconds() > currentRecipe->baseProcessingTime) {
			currentlyProcessing = false;
		}
	}	
}
