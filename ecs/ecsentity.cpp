#include "ecsentity.hpp"

uint ECSEntity::registeredIDs = 0;
uint ECSEntity::RegisterNewID()
{
	return ++registeredIDs;
}

ECSEntity::ECSEntity()
{
	// initialize component array to be all false (no components).
	for (uint i = 0; i < ComponentType::NUMBER_OF_COMPONENTS; i++)
	{
		m_components[i] = false;
	}

	// register a new ID.
	m_ID = RegisterNewID();
	std::cout << "Registering new entity: " << m_ID << std::endl;
}
ECSEntity::~ECSEntity() {}

uint ECSEntity::getID()
{
	return m_ID;
}

bool ECSEntity::hasComponent(ComponentType componentType)
{
	return m_components[componentType];
}

void ECSEntity::giveComponent(ComponentType componentType)
{
	m_components[(uint)componentType] = true;
}
