#pragma once

#include <stddef.h>
#include "../utilities.hpp"

/* ECS COMPONENTS:
 * 
 * Each component must have:
 * 1. a handle for the Entity that contains it. 
 * 2. an ID for this component type.
 * 3. whatever data the particular component is designed to have.
 *
 * The BaseECS Component struct will be non-templated to have an Entity handle and size.
 * A new struct called "ECSComponent" will be templated and inherit from this struct.
 * This can be done to have variables on a component-type-basis, rather than for
 * all components.
 *
 * NOTE: Keep all Template implentations in the header file.
 */

enum ComponentType
{
	Position = 0,
	Velocity,
	Transform,
	Mesh,
	Physics,
	Input,

	NUMBER_OF_COMPONENTS
};


struct BaseECSComponent
{
public:

	// getters/setters:
	uint getPointerID();
	void setPointerID(uint pointerID);
	uint getEntityHandle();
	void setEntityHandle(uint entityID);
	virtual ComponentType getType();

	virtual ~BaseECSComponent() {}

private:

	uint m_entityHandle; // default unassigned to any entity.	
	uint m_pointerID;

protected:

	ComponentType m_componentType;

};


template<typename TComponent>
struct ECSComponent : public BaseECSComponent
{
public:

	ComponentType getType() override;
	static size_t getSize();

protected:

	// must be initialized in the constructor.

	static const size_t m_size;

};


template<typename TComponent>
ComponentType ECSComponent<TComponent>::getType()
{
	return m_componentType;
}

template<typename TComponent>
size_t ECSComponent<TComponent>::getSize()
{
	return m_size;
}

template<typename TComponent>
const size_t ECSComponent<TComponent>::m_size(sizeof(TComponent)); // list initialization.


// TEST COMPONENTS:
struct PositionComponent : public ECSComponent<PositionComponent>
{
	PositionComponent();
	PositionComponent(uint entityID, float x_, float y_);
	float x, y;
};

struct VelocityComponent : public ECSComponent<VelocityComponent>
{
	VelocityComponent();
	VelocityComponent(uint entityID, float vx_, float vy_);
	float vx, vy;
};














