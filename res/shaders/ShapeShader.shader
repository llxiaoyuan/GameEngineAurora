VERTEX
#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 vertexColor;

uniform mat4 proj;

void main()
{
	gl_Position = proj * position;
	vertexColor = color;
};

FRAGMENT
#version 430 core

in vec4 vertexColor;

out vec4 color;

void main()
{
	color = vertexColor;
};
