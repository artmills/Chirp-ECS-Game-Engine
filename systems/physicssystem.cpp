#include "physicssystem.hpp"

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::Start()
{


}

void PhysicsSystem::Update(float dt)
{
	// test: update all transform components with gravity.
	// x_f = x_0 + gt
	std::vector<TransformComponent>& transforms = m_transformComponents.getArray();	
	for (uint i = 0; i < m_transformComponents.NumberOfComponents(); i++)
	{
		TransformComponent& transform = transforms[i]; // safe to access by [] since i is indexing through the component array, not by handle.
		//std::cout << transform.z() << std::endl;
		uint entityID = transform.getEntityHandle();

		uint physicsIndex = m_entities[entityID][1];
		if (physicsIndex != -1) // check if the entity does actually have this component.
		{
			PhysicsComponent* physics = m_physicsComponents.getComponent(physicsIndex);
			if (physics != nullptr) // check if the pointer points to deleted component.
			{
				float dx, dy, dz;
				
				// check if there is an input component that needs to be read.
				uint inputIndex = m_entities[entityID][2];
				if (inputIndex != -1)
				{
					InputComponent* input = m_inputComponents.getComponent(inputIndex);
					if (input != nullptr)
					{
						dx = velocity * (input->getHorizontalMotion()) * dt;
						dy = (gravity + velocity * input->getVerticalMotion()) * dt;
						dz = zAccel * velocity * (input->getDepthMotion()) * dt;
					}
				}
				else
				{
					dx = 0;
					dy = gravity * dt;
					dz = 0;
				}

				transform.updatePosition(dx, dy, dz); 
			}
		}

	}
}

void PhysicsSystem::RegisterEntity(uint entityID, TransformComponent& transform, PhysicsComponent& physics)
{
	// add the relevant components of the entity to the proper arrays.
	int transformHandle = m_transformComponents.AddComponent(transform);
	int physicsHandle = m_physicsComponents.AddComponent(physics);

	// register the handles for these components to the hash map.
	std::vector<int> handles { transformHandle, physicsHandle, -1 }; // no input.
	m_entities.emplace(entityID, handles);

	std::cout << "Registering physics-enabled entity " << entityID << " with components at " << transformHandle << " and " << physicsHandle << std::endl;
}
void PhysicsSystem::RegisterEntity(uint entityID, TransformComponent& transform, PhysicsComponent& physics, InputComponent& input)
{
	// add the relevant components of the entity to the proper arrays.
	int transformHandle = m_transformComponents.AddComponent(transform);
	int physicsHandle = m_physicsComponents.AddComponent(physics);
	int inputHandle = m_inputComponents.AddComponent(input);

	// register the handles for these components to the hash map.
	std::vector<int> handles { transformHandle, physicsHandle, inputHandle };
	m_entities.emplace(entityID, handles);

	std::cout << "Registering physics-enabled entity with input called " << entityID << " with components at " << transformHandle << " and " << physicsHandle << " and " << inputHandle << std::endl;
}

void PhysicsSystem::DeregisterEntity(uint entityID)
{
	// remove components first:
	DeleteComponent(ComponentType::Transform, m_entities[entityID][0]);
	DeleteComponent(ComponentType::Physics, m_entities[entityID][1]);
	DeleteComponent(ComponentType::Input, m_entities[entityID][2]);

	m_entities.erase(entityID);
}

void PhysicsSystem::DeleteComponent(ComponentType componentType, uint handle)
{
	switch (componentType)
	{
		case ComponentType::Transform:
			m_transformComponents.RemoveComponent(handle);
			break;
		case ComponentType::Physics:
			m_physicsComponents.RemoveComponent(handle);
			break;
		case ComponentType::Input:
			m_inputComponents.RemoveComponent(handle);
		default:
			break;
	}
}

void PhysicsSystem::SynchronizeInputs(ECSComponentArray<InputComponent>& from)
{
	m_inputComponents.TrustCopyFrom(from);	
}
void PhysicsSystem::SynchronizeTransforms(ECSComponentArray<TransformComponent>& from)
{
	m_transformComponents.TrustCopyFrom(from);	
}

ECSComponentArray<TransformComponent>& PhysicsSystem::ExportTransforms()
{
	return m_transformComponents;
}

void PhysicsSystem::PrintArrays()
{
	/*std::vector<PositionComponent>& positions = positionComponents.getArray();
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
	}*/
}






























