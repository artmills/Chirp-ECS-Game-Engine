#include "ecscomponentmanager.hpp"

ECSComponentManager::ECSComponentManager()
{
}


void ECSComponentManager::PrintComponentArrays()
{
	for (auto it = positions.getArray().begin(); it != positions.getArray().end(); it++)
	{
		std::cout << "x = " << it->x << ". y = " << it->y << std::endl;
	}
}

void ECSComponentManager::PrintPositionComponentData(ECSEntity& entity)
{
	const PositionComponent& position = positions[entity.getHandle(ComponentType::Position)];
	std::cout << "x = " << position.x << ". y = " << position.y << std::endl;
}


void ECSComponentManager::AddComponent(ECSEntity& entity, BaseECSComponent& component)
{
	// first, make sure that the ECSEntity does not already have a component of this type.
	uint ID = component.getType();
	if (entity.getHandle((ComponentType)ID) != -1)
	{
		std::cout << "ECSEntity already has this component! " << std::endl;
		return;
	}

	// next, set the entity handle on the component.
	component.setEntityHandle(entity.getID());

	// my failures to find a smart way to choose the proper component vector has led me to this.
	switch (ID)
	{
		// add the component to the proper arrays and update the handle of the entity.

	case ComponentType::Position:
		entity.setHandle((ComponentType)ID, positions.AddComponent(component));
		break;

	case ComponentType::Velocity:
		entity.setHandle((ComponentType)ID, velocities.AddComponent(component));
		break;

	default:
		break;
	}
}

void ECSComponentManager::RemoveComponent(ECSEntity& entity, ComponentType componentType)
{
	// use the handle of the entity to get the pointer to the proper component.
	// using the pointer value and the value of the first element in the component array,
	// as well as the size of the component type, we can find the index of the component
	// in the component array.
	// swap the component we want to delete with the last component in the list.
	// delete the last elements in both the pointer and component arrays.
	
	// first, check to make sure that the entity actually has a component here.
	if (entity.getHandle(componentType) == -1)
	{
		std::cout << "Entity already has no components here! " << std::endl;
		return;
	}

	entity.setHandle(componentType, -1);

	switch (componentType)
	{
	case ComponentType::Position:
		positions.RemoveComponent(entity.getHandle(ComponentType::Position));
		break;

	case ComponentType::Velocity:
		velocities.RemoveComponent(entity.getHandle(ComponentType::Velocity));
		break;

	default:
		break;
	}
}


























