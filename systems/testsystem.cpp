#include "testsystem.hpp"

TestSystem::TestSystem() {}

void TestSystem::Start()
{


}

void TestSystem::Update(float dt)
{
	// test: update all position components by reading their velocities and calculating
	// x_f = x_0 + v(dt).
	std::vector<PositionComponent>& positions = positionComponents.getArray();	
	for (uint i = 0; i < positionComponents.NumberOfComponents(); i++)
	{
		PositionComponent& position = positions[i]; // safe to access by [] since i is indexing through the component array, not by handle.
		uint entityID = position.getEntityHandle();

		uint velocityIndex = m_entities[entityID][1];
		if (velocityIndex != -1) // check if the entity does actually have this component.
		{
			VelocityComponent* velocity = velocityComponents.getComponent(velocityIndex);
			if (velocity != nullptr) // check if the pointer points to deleted component.
			{
				position.x += velocity->vx * dt;
				position.y += velocity->vy * dt;
			}
		}

	}
}

void TestSystem::RegisterEntity(uint entityID, PositionComponent& position, VelocityComponent& velocity)
{
	// add the relevant components of the entity to the proper arrays.
	int posHandle = positionComponents.AddComponent(position);
	int velHandle = velocityComponents.AddComponent(velocity);

	// register the handles for these components to the hash map.
	std::vector<int> handles { posHandle, velHandle };
	m_entities.emplace(entityID, handles);

	std::cout << "Registering entity " << entityID << " with components at " << posHandle << " and " << velHandle << std::endl;
}

void TestSystem::DeregisterEntity(uint entityID)
{
	// remove components first:
	DeleteComponent(ComponentType::Position, m_entities[entityID][0]);
	DeleteComponent(ComponentType::Velocity, m_entities[entityID][1]);

	m_entities.erase(entityID);
}

void TestSystem::DeleteComponent(ComponentType componentType, uint handle)
{
	switch (componentType)
	{
		case ComponentType::Position:
			positionComponents.RemoveComponent(handle);
			break;
		case ComponentType::Velocity:
			velocityComponents.RemoveComponent(handle);
			break;
		default:
			break;
	}
}

void TestSystem::SynchronizePositions(ECSComponentArray<PositionComponent>& from)
{
	positionComponents.TrustCopyFrom(from);	
}

ECSComponentArray<PositionComponent>& TestSystem::ExportPositions()
{
	return positionComponents;
}

void TestSystem::PrintArrays()
{
	std::vector<PositionComponent>& positions = positionComponents.getArray();
	for (uint i = 0; i < positions.size(); i++)
	{
		PositionComponent& position = positions[i];
		uint entityID = position.getEntityHandle();
		uint velocityHandle = m_entities[entityID][1];
		VelocityComponent* velocity = velocityComponents.getComponent(velocityHandle);
		if (velocityHandle == -1 || velocity == nullptr)
		{
			std::cout << "Entity " << entityID << " has coordinates " << position.x << "," << position.y << " but does not have a velocity. " << std::endl;
		}
		else
		{
			std::cout << "Entity " << entityID << " has coordinates " << position.x << "," << position.y << " with velocity " << velocity->vx << "," << velocity->vy << std::endl;
		}
		std::cout << std::endl;
	}
}






























