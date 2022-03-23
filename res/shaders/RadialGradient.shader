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

out vec4 fragColor;

void main()
{
	vec2 pos_ndc=2.0*(gl_FragCoord.xy-vec2(200.0,100.0))/vec2(500.0,500.0)-1.0;

	float dst=length(pos_ndc);

	vec4 white = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 red = vec4(1.0, 0.627, 0.078, 0.2);
    vec4 blue = vec4(1.0, 0.549, 0.078, 0.11);
    vec4 green = vec4(1.0, 0.470, 0.078, 0.0);
    
    float step1 = 0.024;
    float step2 = 0.125;
    float step3 = 0.32;
    float step4 = 1.0;

	vec4 color = mix(white, red, smoothstep(step1, step2, dst));
    color = mix(color, blue, smoothstep(step2, step3, dst));
    color = mix(color, green, smoothstep(step3, step4, dst));

	fragColor=color;
};
