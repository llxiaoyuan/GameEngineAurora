COMPUTE
#version 430 core

layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform imageBuffer velocity_buffer;
layout(rgba32f, binding = 1) uniform imageBuffer position_buffer;

uniform float dt = 0.01;

uniform int state = -1;

uniform vec4 mousePos = vec4(960, 540, 0, 1);

void main(void)
{
	vec4 vel = imageLoad(velocity_buffer, int(gl_GlobalInvocationID.x));
	vec4 pos = imageLoad(position_buffer, int(gl_GlobalInvocationID.x));

	vec3 dst = mousePos.xyz - pos.xyz;

	float len = length(dst);

	float forceX = 500000 * dst.x / (len * len + 100.0);

	float forceY = 500000 * dst.y / (len * len + 100.0);

	vec3 acc = vec3(forceX, forceY, 0);

	vel.xyz += acc * dt;

	pos.xyz += vel.xyz * dt;

	imageStore(position_buffer, int(gl_GlobalInvocationID.x), pos);
	imageStore(velocity_buffer, int(gl_GlobalInvocationID.x), vel);
}