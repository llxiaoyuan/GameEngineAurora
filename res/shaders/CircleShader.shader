VERTEX
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 circlePos;
layout(location = 2) in vec4 circleColor;
layout(location = 3) in float circleLength;

out vec4 MyCircleColor;

uniform mat4 proj;

void main()
{
	gl_Position = proj * (vec4(circleLength, circleLength, 1, 1) * position + vec4(circlePos, 0, 0));
	MyCircleColor=circleColor;
};

FRAGMENT
#version 330 core

in vec4 MyCircleColor;

out vec4 color;

void main()
{
	color = MyCircleColor;
};
