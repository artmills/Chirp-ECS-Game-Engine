#pragma once

#include <stddef.h>
#include "../utilities.hpp"



/** Type of component this is.
 *
 * One type for a container of data.
 *
 * Each of these types will be thrown into a list of components of the same type.
 * Then the corresponding ECSSystem will iterate over this list to perform its calculations. 
 * Whenever a new component is added, a new entry should be added to this struct. */
enum ComponentType
{
	Position = 0,
	Velocity,
	Transform,
	Grid,
	Mesh,
	Physics,
	Input,

	NUMBER_OF_COMPONENTS
};


/** ECS COMPONENTS:
 * 
 * Each component must have:
 *
 * 1) A handle for the Entity that contains it. 
 * 2) An ID for the pointer that points to this component in the handle manager.
 * 3) An ID for this component type.
 * 4) Whatever data the particular component is designed to have.
 *
 * The BaseECS Component struct will be non-templated to have an Entity handle and size.
 * A new struct called "ECSComponent" will be templated and inherit from this struct.
 * This can be done to have variables on a component-type-basis, rather than for all components.
 *
 * NOTE: Keep all Template implentations in the header file.
 */
struct BaseECSComponent
{
public:

	/** Get the ID of the pointer that points to this component in the handle manager. */
	uint getPointerID();


	/** Set the ID of the pointer pointing to this component. This must always be done when registering a component to an entity. */
	void setPointerID(uint pointerID);


	/** Get the ID of the entity that has this component. */
	uint getEntityHandle();


	/** Register this component to an entity. */
	void setEntityHandle(uint entityID);


	/** Get the type of component this is. */
	virtual ComponentType getType();

	virtual ~BaseECSComponent() {}

private:

	/** ID of the entity that has this component. */
	uint m_entityHandle;


	/** ID of the pointer that keeps track of this entity in the handle manager. */
	uint m_pointerID;

protected:

	/** Keep track of the type of component this is. */
	ComponentType m_componentType;

};


/** ECSComponent inherits from BaseECSComponent, templated under the type of component this is. */
template<typename TComponent>
struct ECSComponent : public BaseECSComponent
{
public:

	/** Get the specific type of component this is. */
	ComponentType getType() override;


	/** Total size of the data in this component. 
	 * This depends only on the component type. */
	static size_t getSize();

protected:

	/** Must be initialized in the constructor. */
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
