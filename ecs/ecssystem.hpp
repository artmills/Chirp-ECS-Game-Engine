#pragma once

#include "ecsentity.hpp"
#include "ecscomponentarray.hpp"

// abstract class. any system requires the following methods.
class ECSSystem
{
public:

	// initilization function. equivalent to Start() in Unity. prepares data for when the system 
	// first starts.
	virtual void Start() = 0;

	// update. where the logic occurs.
	virtual void Update(float dt) = 0;

	// delete a component and its dependencies.
	virtual void DeleteComponent(ComponentType componentType, uint index) = 0;

	virtual ~ECSSystem() {}

private:

	// mark a component and its dependencies for deletion. do not delete a component
	// right away -- do it after the main logic in Update() is done.
	//virtual void MarkForDeletion(ComponentType componentType, uint index) = 0;

};
