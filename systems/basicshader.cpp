#include "basicshader.hpp"

// get the shader file for this shader and handle the OpenGL functions to prepare it.
BasicShader::BasicShader() : ShaderProgram()
{
	// despite how header files work, referencing a file as a string like this
	// is done relative to the location of the makefile, I guess.
	m_shaderFile = "systems/res/shaders/basic.shader";
}
BasicShader::~BasicShader() {}

void BasicShader::Initialize()
{
	PrepareShader(m_shaderFile);
}

// bind position, color, etc.
void BasicShader::BindAttributes()
{
	BindAttribute(0, "vPosition");
	BindAttribute(1, "vColor");
}

// get uniform locations so uniforms can be bound to the correct shader variables.
void BasicShader::GetAllUniformLocations()
{
	m_locationModelViewProjectionMatrix = GetUniformLocation("uModelViewProjectionMatrix");
}

// only need one matrix: modelViewProjection = model * view * projection.
void BasicShader::LoadModelViewProjectionMatrix(glm::mat4& mvp)
{
	//PrintRowMajor(mvp);
	LoadUniform(m_locationModelViewProjectionMatrix, mvp);
}

std::string BasicShader::m_shaderFile;


void BasicShader::PrintRowMajor(glm::mat4& matrix)
{
	for (uint i = 0; i < 4; i++)
	{
		for (uint j = 0; j < 4; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
