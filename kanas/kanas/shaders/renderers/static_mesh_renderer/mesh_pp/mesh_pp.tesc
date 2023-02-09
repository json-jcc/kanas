#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_shading_language_include : require
#pragma STDGL invariant(all)
#pragma optimize(on)
#pragma debug(on)
#include "/common.glsl" //! #include "../../templates/common.glsl"

layout(vertices = 3) out;

in TescData
{
	vec3 position;
	vec2 uv;
	vec3 normal;
 } inData[];

 out TeseData
 {
	vec3 position;
	vec2 uv;
	vec3 normal;
 } outData[];

void main()
{
	outData[gl_InvocationID].position = inData[gl_InvocationID].position;
	outData[gl_InvocationID].normal = inData[gl_InvocationID].normal;
	outData[gl_InvocationID].uv = inData[gl_InvocationID].uv;

	float distance0 = distance(camera_position, inData[0].position); 
	float distance1 = distance(camera_position, inData[1].position); 
	float distance2 = distance(camera_position, inData[2].position); 

	if (gl_InvocationID == 0)
	{
		gl_TessLevelOuter[0] = GetTessLevel(distance1, distance2);
		gl_TessLevelOuter[1] = GetTessLevel(distance2, distance0);
		gl_TessLevelOuter[2] = GetTessLevel(distance0,distance1);
		gl_TessLevelInner[0] = gl_TessLevelOuter[2];
	}
}

