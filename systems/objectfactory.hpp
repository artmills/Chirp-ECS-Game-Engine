#pragma once

#include "../ecs/ecsentity.hpp"
#include "../ecs/ecscomponent.hpp"

// TODO: 
// event system as described below for adding entities to systems.
// sort the vector of BaseECSComponent* in CreateEntity methods before adding
//		to systems.

// for now, include references to systems.
// later, implement an event system that sends "create entity" events to systems.
#include "rendersystem.hpp"
#include "physicssystem.hpp"
#include "inputsystem.hpp"
#include "terrainfactory.hpp"

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
	void CreateEntity_Terrain(float x, float y, float z, int width, int height, float blockSize, int percent, int affinity, int smooth);

private: 

	void RegisterToSystems(ECSEntity& entity, std::vector<BaseECSComponent*>& components);	
	RenderSystem* renderSystem = nullptr;
	PhysicsSystem* physicsSystem = nullptr;
	InputSystem* inputSystem = nullptr;
};
