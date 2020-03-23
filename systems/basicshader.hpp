#pragma once

#include "glm/glm.hpp"
#include <iostream>

#include "../utilities.hpp"
#include "shaderprogram.hpp"

/** Implementation of a basic shader program.
 *
 * This shader accounts for the following attributes:
 *
 * 1) vec3 vPosition
 * 2) vec4 vColor
 *
 * and the following uniforms:
 *
 * 1) mat4 uModelViewProjection
 */
class BasicShader : public ShaderProgram
{
public:

	/** Initialize the location of the shader source file. */
	BasicShader();
	~BasicShader();


	/** Call PrepareShader(). */
	void Initialize();


	/** Load the given MVP matrix as a uniform. */
	void LoadModelViewProjectionMatrix(glm::mat4& mvp);

private:

	/** Path to shader source file. */
	static std::string m_shaderFile;


	/** ID of the MVP matrix given by GetUniformLocation(mvp). */
	uint m_locationModelViewProjectionMatrix;


	/** Debug print method. This really shouldn't be here. */
	void PrintRowMajor(glm::mat4& matrix);

protected:

	// overrides:
	void BindAttributes();
	void GetAllUniformLocations();

};

