#pragma once

class ECSEntity;

#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

#include "ecsentity.hpp"
#include "ecscomponent.hpp"
#include "ecscomponentarray.hpp"

// contains arrays of all of the components in a larger array. the correct array is
// identified by the ID number of each component type determined by ECSComponent.
class ECSComponentManager
{
public:

	ECSComponentManager();

	// manage components:
	void AddComponent(ECSEntity& entity, BaseECSComponent& component);
	void RemoveComponent(ECSEntity& entity, ComponentType componentType);

	// debug:
	void PrintComponentArrays();
	void PrintPositionComponentData(ECSEntity& entity);

private:

	// the components will be stored in their own vectors.
	// sadly, I couldn't figure out how to make vectors of arbitrary components work.
	// maps and vectors of a base class T fail because placing objects of derived class
	// T' into these structures casts them to object T, which will probably have a smaller
	// memory size. then dynamically casting them back to T' will cause a seg fault
	// when accessing the members unique to T'. 
	// apparently, a dictionary of map<ID, vector<ECSComponent> * > doesn't work.
	
	// custom component arrays:
	ECSComponentArray<PositionComponent> positions;
	ECSComponentArray<VelocityComponent> velocities;
};


































