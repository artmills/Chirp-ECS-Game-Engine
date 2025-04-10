#include "ecscomponent.hpp"

// necessary global variable to keep track of what IDs have been registered to components.
// the alternative would be to keep track of this in another class like ComponentManager,
// but then m_ID would not be able to be static const.


// BASE ECSCOMPONENT:
ComponentType BaseECSComponent::getType()
{
	return ComponentType::NUMBER_OF_COMPONENTS;
}

uint BaseECSComponent::getEntityHandle()
{
	return m_entityHandle;
}
void BaseECSComponent::setEntityHandle(uint entityID)
{
	m_entityHandle = entityID;
}
uint BaseECSComponent::getPointerID()
{
	return m_pointerID;
}
void BaseECSComponent::setPointerID(uint pointerID)
{
	m_pointerID = pointerID;
}

