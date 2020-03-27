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


	/** Create a terrain with the following parameters:
	 *
	 * xChunks, yChunks: number of chunks in the x,y-direction.
	 *
	 * width, height: size of each individual chunk.
	 *
	 * x, y, z: location of the bottom-left corner of the entire terrain.
	 *
	 * blockSize: size of each block in the grid making up the terrain.
	 *
	 * percent, affinity, smooth: parameters for CA. the initial random percent the grid is filled to, the number of active neighbors needed to activate a square, the number of times CA should be run. */
	void CreateTerrain(int xChunks, int yChunks, int width, int height, float xT, float yT, float zT, float blockSize, int percent, int affinity, int smooth);

private: 

	void RegisterToSystems(ECSEntity& entity, std::vector<BaseECSComponent*>& components);	
	RenderSystem* renderSystem = nullptr;
	PhysicsSystem* physicsSystem = nullptr;
	InputSystem* inputSystem = nullptr;
};
