VERTEX
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 lineColor;

out vec4 MyLineColor;

uniform mat4 proj;

void main()
{
	gl_Position = proj * position;
	MyLineColor=lineColor;
};

FRAGMENT
#version 330 core

in vec4 MyLineColor;

out vec4 color;

void main()
{
	color = MyLineColor;
};
