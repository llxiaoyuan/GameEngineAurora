VERTEX
#version 430 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in float width;

out VS_OUT{
	float width;
	vec4 color;
} vs_out;

void main()
{
	gl_Position = position;
	vs_out.color = color;
	vs_out.width = width;
}

FRAGMENT
#version 430 core

in vec4 color;

out vec4 FragColor;

void main()
{
	FragColor = color;
}

GEOMETRY
#version 430 core

layout(lines) in;
layout(triangle_strip, max_vertices = 120) out;

in VS_OUT{
	 float width;
	vec4 color;
} gs_in[];

out vec4 color;

float width;

uniform mat4 proj;
//也许可以优化
void main() {

	width = gs_in[0].width;

	color = gs_in[0].color;

	vec4 dir = normalize(gl_in[1].gl_Position - gl_in[0].gl_Position);

	float theta = atan(dir.x, -dir.y);

	gl_Position = proj * (gl_in[0].gl_Position + width * vec4(cos(theta), sin(theta), 0.0, 0.0));
	EmitVertex();
	gl_Position = proj * gl_in[0].gl_Position;
	EmitVertex();
	theta += 3.1415926535 / 8;
	gl_Position = proj * (gl_in[0].gl_Position + width * vec4(cos(theta), sin(theta), 0.0, 0.0));
	EmitVertex();
	gl_Position = proj * gl_in[0].gl_Position;
	EmitVertex();

	for (int i = 0; i < 7; i++)
	{
		theta += 3.1415926535 / 8;
		gl_Position = proj * (gl_in[0].gl_Position + width * vec4(cos(theta), sin(theta), 0.0, 0.0));
		EmitVertex();
		gl_Position = proj * gl_in[0].gl_Position;
		EmitVertex();
	}

	theta -= 3.1415926535 / 8;

	for (int i = 0; i < 9; i++)
	{
		theta += 3.1415926535 / 8;
		gl_Position = proj * (gl_in[1].gl_Position + width * vec4(cos(theta), sin(theta), 0.0, 0.0));
		EmitVertex();
		gl_Position = proj * gl_in[0].gl_Position;
		EmitVertex();
	}

	gl_Position = proj * (gl_in[0].gl_Position + width * vec4(cos(theta), sin(theta), 0.0, 0.0));
	EmitVertex();


	EndPrimitive();
}