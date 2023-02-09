#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_shading_language_include : require
#pragma STDGL invariant(all)
#pragma optimize(on)
#pragma debug(on)
#include "/common.glsl" //! #include "../../templates/common.glsl"

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

 in GeomData
 {
	vec3 position;
	vec2 uv;
	vec3 normal;
	float disp;
 } inData[];

out FragData
{
	vec3 position;
	vec2 uv;
	vec3 normal;
	float disp;
} outData;

void main()
{
	for(int i = 0; i < 3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		outData.position = inData[i].position;
		outData.uv = inData[i].uv;
		outData.normal = inData[i].normal;
		outData.disp = inData[i].disp;
		EmitVertex();
	}
	EndPrimitive();
}
