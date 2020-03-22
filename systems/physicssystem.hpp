#pragma once

#include <unordered_map>

#include "../ecs/ecssystem.hpp"
#include "../components/transformcomponent.hpp"
#include "../components/physicscomponent.hpp"
#include "../components/inputcomponent.hpp"

// test physics system that simulates gravity.
// uses the transform and physics components.
class PhysicsSystem : public ECSSystem
{

public:

	PhysicsSystem();

	const float gravity = -0.003f;
	const float velocity = 1.00f;
	const float zAccel = 6.0f;

	// initilization function. equivalent to Start() in Unity. prepares data for when the system 
	// first starts.
	void Start() override;

	// update. main function for the system. runs every dt seconds.
	void Update(float dt) override;

	// register an entity by copying its components into the copies of the component
	// arrays.
	void RegisterEntity(uint entityID, TransformComponent& transform, PhysicsComponent& physics);
	void RegisterEntity(uint entityID, TransformComponent& transform, PhysicsComponent& physics, InputComponent& input);

	// delete an entity and its components.
	void DeregisterEntity(uint entityID);

	// delete a component.
	void DeleteComponent(ComponentType componentType, uint index) override;

	// synchronize arrays.
	void SynchronizeTransforms(ECSComponentArray<TransformComponent>& from);
	ECSComponentArray<TransformComponent>& ExportTransforms();

	void SynchronizeInputs(ECSComponentArray<InputComponent>& from);

	// debug:
	void PrintArrays();
	
private:

	// hash map to keep track of entities and their components:
	std::unordered_map<uint, std::vector<int> > m_entities;	

	// component arrays:
	ECSComponentArray<TransformComponent> m_transformComponents; // master copy.
	ECSComponentArray<PhysicsComponent> m_physicsComponents; // master copy.
	ECSComponentArray<InputComponent> m_inputComponents;
};







