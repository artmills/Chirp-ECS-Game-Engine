#pragma once

#include <unordered_map>

#include "../ecs/ecssystem.hpp"


// test system that implements the ECSSystem abstract class.
// uses a Position and Velocity component.
class TestSystem : public ECSSystem
{

public:

	TestSystem();

	// initilization function. equivalent to Start() in Unity. prepares data for when the system 
	// first starts.
	void Start() override;

	// update. main function for the system. runs every dt seconds.
	void Update(float dt) override;

	// register an entity by copying its components into the copies of the component
	// arrays.
	void RegisterEntity(uint entityID, PositionComponent& position, VelocityComponent& velocity);

	// delete an entity and its components.
	void DeregisterEntity(uint entityID);

	// delete a component.
	void DeleteComponent(ComponentType componentType, uint index) override;

	// synchronize arrays.
	void SynchronizePositions(ECSComponentArray<PositionComponent>& from);
	ECSComponentArray<PositionComponent>& ExportPositions();

	// debug:
	void PrintArrays();
	
private:

	// hash map to keep track of entities and their components:
	std::unordered_map<uint, std::vector<int> > m_entities;	

	// component arrays:
	ECSComponentArray<PositionComponent> positionComponents; // master copy.
	ECSComponentArray<VelocityComponent> velocityComponents; // master copy.
};
