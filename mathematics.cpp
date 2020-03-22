#include "mathematics.hpp"

glm::mat4 Mathematics::GetTranslationMatrix(float x, float y, float z)
{
	glm::vec3 translation{ x, y, z };
	glm::mat4 identity = glm::mat4(1.0f); //first set to identity.

	return glm::translate(identity, translation);
}

glm::mat4 Mathematics::GetTransformationMatrix(TransformComponent& transform)
{
	glm::mat4 identity = glm::mat4(1.0f);
	return glm::translate(identity, transform.getPosition());
}

void Mathematics::GetPerspectiveFieldOfViewMatrix(glm::mat4& matrix, float fieldOfView, uint width, uint height, float nearPlane, float farPlane)
{
	matrix = glm::perspective(fieldOfView, (float)width / (float)height, nearPlane, farPlane);
}

/*glm::mat4 Mathematics::GetViewMatrix(Camera* camera)
{
	glm::vec3 position = (*camera).get_position();
	glm::vec3 rotation = (*camera).get_rotation();

	glm::mat4 identity = glm::mat4(1.0f);
	glm::mat4 pitch = glm::rotate(identity, rotation.x, glm::vec3{ 1, 0, 0 });
	glm::mat4 yaw = glm::rotate(pitch, rotation.y, glm::vec3{ 0, 1, 0 });
	glm::mat4 negativeCameraPosition = glm::translate(yaw, -position);

	return negativeCameraPosition;
}*/


Mathematics::Mathematics()
{
}


Mathematics::~Mathematics()
{
}
