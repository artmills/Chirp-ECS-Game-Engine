#include "transformcomponent.hpp"

TransformComponent::TransformComponent(uint entityID, float x, float y, float z, float rx, float ry, float rz)
	: position(glm::vec3(x, y, z)), rotation(glm::vec3(rx, ry, rz))
{
	setEntityHandle(entityID);
	m_componentType = ComponentType::Transform;
}
TransformComponent::TransformComponent(uint entityID, glm::vec3 _position, glm::vec3 _rotation)
	: position(_position), rotation(_rotation)
{
	setEntityHandle(entityID);
	m_componentType = ComponentType::Transform;
}

glm::vec3 TransformComponent::getPosition()
{
	return position;
}
glm::vec3 TransformComponent::getRotation()
{
	return rotation;
}

float TransformComponent::x()
{
	return position.x;
}
float TransformComponent::y()
{
	return position.y;
}
float TransformComponent::z()
{
	return position.z;
}
float TransformComponent::rx()
{
	return rotation.x;
}
float TransformComponent::ry()
{
	return rotation.y;
}
float TransformComponent::rz()
{
	return rotation.z;
}

void TransformComponent::setPosition(glm::vec3 _position)
{
	position = _position;
}
void TransformComponent::setRotation(glm::vec3 _rotation)
{
	rotation = _rotation;
}
void TransformComponent::setPosition(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
}
void TransformComponent::setRotation(float rx, float ry, float rz)
{
	rotation = glm::vec3(rx, ry, rz);
}

void TransformComponent::updatePosition(float dx, float dy, float dz)
{
	position += glm::vec3(dx, dy, dz);
}
void TransformComponent::updateRotation(float dx, float dy, float dz)
{
	rotation += glm::vec3(dx, dy, dz);
}
void TransformComponent::updatePosition(glm::vec3 dPosition)
{
	position += dPosition;
}
void TransformComponent::updateRotation(glm::vec3 dRotation)
{
	rotation += dRotation;
}













