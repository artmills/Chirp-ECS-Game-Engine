#shader vertex
#version 400 core

in vec4 vPosition;
in vec4 vColor;

out vec4 fColor;

uniform mat4 uModelViewProjectionMatrix;

void main()
{
	gl_Position = uModelViewProjectionMatrix * vPosition;
	//gl_Position = vPosition;

	fColor = vColor;
};


#shader fragment
#version 400 core

in vec4 fColor;

out vec4 color;

void main()
{
	color = fColor;
};
