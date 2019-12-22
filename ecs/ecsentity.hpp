#pragma once

#include <iostream>
#include "ecscomponent.hpp"

// entities in ECS only contain an ID for themselves and an array of bools that
// represent their components.
class ECSEntity
{
public:

	ECSEntity();
	~ECSEntity();

	uint getID();
	bool hasComponent(ComponentType componentType);
	void giveComponent(ComponentType componentType);

private:

	static uint registeredIDs; // keeps track of which IDs have been registered.
	static uint RegisterNewID(); // gives the entity an ID.
	uint m_ID; // ID of this particular entity.

	// this will be an array of handles into an array of pointers that point to the components.
	// the array will be of size NUMBER OF COMPONENTS, where the element indices
	// correspond to the enum uint values from ComponentType.
	// a handle value of false means no component has been added.
	bool m_components[ComponentType::NUMBER_OF_COMPONENTS];

};
