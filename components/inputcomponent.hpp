#pragma once

#include <iostream>
#include "../ecs/ecscomponent.hpp"

// information about inputs.
// fields will correspond to the ACTIONS done by pressing a button.
// the input manager will figure out key-mapping from buttons to actions.
// the physics system will calculate velocity.
struct InputComponent : public ECSComponent<InputComponent>
{
public:

	// motion:
	void setHorizontalMotion(float input);	
	void setVerticalMotion(float input);	
	void setDepthMotion(float input);	
	float getHorizontalMotion();
	float getVerticalMotion();
	float getDepthMotion();

	void Reset(); // reset all inputs after each frame.

private:

	float horizontalMotion = 0; // default a, d keys.
	float verticalMotion = 0; // default w, s keys.
	float depthMotion = 0; // default t, g keys.

};
