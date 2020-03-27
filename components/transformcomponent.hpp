#pragma once

#include "glm/glm.hpp"

#include "../ecs/ecscomponent.hpp"

/** Data to describe an object's location and orientation. */
struct TransformComponent : public ECSComponent<TransformComponent>
{
public:

	TransformComponent(uint entityID, float x, float y, float z, float rx, float ry, float rz);
	TransformComponent(uint entityID, glm::vec3 position, glm::vec3 rotation);

	// getters/setters:
	glm::vec3 getPosition();
	glm::vec3 getRotation();
	
	float x();
	float y();
	float z();
	float rx();
	float ry();
	float rz();

	void setPosition(glm::vec3 _position);
	void setPosition(float x, float y, float z);
	void setRotation(glm::vec3 _rotation);
	void setRotation(float rx, float ry, float rz);

	// update: equivalent to += another vector.
	void updatePosition(float dx, float dy, float dz);
	void updateRotation(float dx, float dy, float dz);
	void updatePosition(glm::vec3 dPosition);
	void updateRotation(glm::vec3 dRotation);

private:

	glm::vec3 position;
	glm::vec3 rotation;

};
	
