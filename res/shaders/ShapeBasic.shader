VERTEX
#version 330 core
layout(location = 0) in vec2 aPos;

uniform mat4 proj;

void main()
{
	gl_Position = proj * vec4(aPos.x, aPos.y, 0.0, 1.0);
}

FRAGMENT
#version 330 core

uniform vec4 u_color;

out vec4 FragColor;

void main()
{
	FragColor = u_color;
}