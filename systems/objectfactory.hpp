#pragma once

#include "../ecs/ecsentity.hpp"
#include "../ecs/ecscomponent.hpp"

// TODO: 
// event system as described below for adding entities to systems.
// sort the vector of BaseECSComponent* in CreateEntity methods before adding
//		to systems.

// for now, include references to systems.
// later, implement an event system that sends "create entity" events to systems.
#include "testsystem.hpp"
#include "rendersystem.hpp"
#include "physicssystem.hpp"
#include "inputsystem.hpp"

#include <vector>

// creates game objects: entities plus their necessary components.
class ObjectFactory
{
public:

	ObjectFactory(RenderSystem* renderSystem, PhysicsSystem* physicsSystem, InputSystem* inputSystem);

	// test blueprints:
	void CreateEntity_Triangle();	
	void CreateEntity_Moveable_Triangle();	
	void CreateEntity_Square(float botLeftX, float botLeftY, float width, float height);

private: 

	void RegisterToSystems(ECSEntity& entity, std::vector<BaseECSComponent*>& components);	
	RenderSystem* renderSystem = nullptr;
	PhysicsSystem* physicsSystem = nullptr;
	InputSystem* inputSystem = nullptr;
};
