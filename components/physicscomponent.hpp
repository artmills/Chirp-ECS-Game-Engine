#pragma once

#include "../ecs/ecscomponent.hpp"

// for now, only serves as a check for whether entities should be affected by physics.
struct PhysicsComponent : public ECSComponent<PhysicsComponent>
{ 
};
