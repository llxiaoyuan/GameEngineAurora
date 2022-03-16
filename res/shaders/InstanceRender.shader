VERTEX
#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in mat4 model;

out vec2 v_TexCoord;

uniform mat4 proj;

void main()
{
	gl_Position = proj * model * position;
	v_TexCoord = texCoord;
};

FRAGMENT
#version 430 core

out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
};
