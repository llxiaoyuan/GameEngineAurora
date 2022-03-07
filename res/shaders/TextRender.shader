VERTEX
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 proj;
uniform mat4 pos;

void main()
{
	gl_Position = proj * pos * position;
	v_TexCoord = texCoord;
};

FRAGMENT
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform vec4 spriteColor;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = spriteColor * texColor;
};
