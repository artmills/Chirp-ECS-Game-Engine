#pragma once

#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
//#include "camera.h"

#include "utilities.hpp"
#include "components/transformcomponent.hpp"

/** Get matrices representing graphical transformations. */
class Mathematics
{
public:

	/** Get a matrix representing translation by (x, y, z). */
	static glm::mat4 GetTranslationMatrix(float x, float y, float z);

	/** Get a matrix representing the transformation given the transform. */
	static glm::mat4 GetTransformationMatrix(TransformComponent& transform);

	/** Get the matrix representing a perspective projection. */
	static void GetPerspectiveFieldOfViewMatrix(glm::mat4& matrix, float fieldOfView, uint width, uint height, float nearPlane, float farPlane);


	//static glm::mat4 GetViewMatrix(Camera* camera);

private:
	Mathematics();
	~Mathematics();
};
