#pragma once

#include <GL/glew.h>
#include "glm/glm.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "../utilities.hpp"

// wrapper for basic shader functions. implement them by creating a new shader class
// that inherits from ShaderProgram.
class ShaderProgram
{
public:

	ShaderProgram();
	~ShaderProgram();

	// load the shader.
	void PrepareShader(const std::string& file);

	// convenient types:
	enum ShaderType
	{
		none = -1, vertex = 0, fragment = 1, tessellation, geometry, compute
	};
	struct ShaderProgramSource // just a way of returning both shader files in a single method.
	{
		std::string vertexSource;
		std::string fragmentSource;
	};

	
	// actual shader functionality.

	void Start();
	void Stop();
	void CleanUp();


private:

	// handles:
	uint m_programID;
	uint m_vertexShaderID;
	uint m_fragmentShaderID;

	// parse and load the shader file:
	static void LoadShader(uint& shaderID, ShaderType shaderType, const std::string& text);
	static ShaderProgramSource ParseShader(const std::string& textfile);

protected:

	// attributes:
	virtual void BindAttributes() = 0; // abstract method. a class that inherits from here will have its own attributes it needs to set up.
	void BindAttribute(int attributeNumber, const std::string& variableName);

	// uniforms:
	virtual void GetAllUniformLocations() = 0;
	uint GetUniformLocation(const std::string& uniformName);

	// load uniforms to GPU:
	void LoadUniform(uint location, glm::mat4& matrix);








};
