#pragma once

#include "glm/glm.hpp"
#include <iostream>

#include "../utilities.hpp"
#include "shaderprogram.hpp"

// basic implementation of a shader.
class BasicShader : public ShaderProgram
{
public:
	BasicShader();
	~BasicShader();

	void Initialize();

	// uniforms.
	void LoadModelViewProjectionMatrix(glm::mat4& mvp);

private:

	// source code:
	static std::string m_shaderFile;

	// uniforms:
	uint m_locationModelViewProjectionMatrix;

	// print:
	void PrintRowMajor(glm::mat4& matrix);

protected:

	// overrides:
	void BindAttributes();
	void GetAllUniformLocations();

};

