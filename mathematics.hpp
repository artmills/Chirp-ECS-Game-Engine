#pragma once

#include "glm/gtc/matrix_transform.hpp"
//#include "camera.h"

#include "utilities.hpp"
#include "components/transformcomponent.hpp"

class Mathematics
{
public:

	static glm::mat4 GetTranslationMatrix(float x, float y, float z);
	static glm::mat4 GetTransformationMatrix(TransformComponent& transform);
	static void GetPerspectiveFieldOfViewMatrix(glm::mat4& matrix, float fieldOfView, uint width, uint height, float nearPlane, float farPlane);
	//static glm::mat4 GetViewMatrix(Camera* camera);

private:
	Mathematics();
	~Mathematics();
};
