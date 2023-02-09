#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_shading_language_include : require
#pragma STDGL invariant(all)
#pragma optimize(on)
#pragma debug(on)
#include "/common.glsl" //! #include "../../templates/common.glsl"

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 mesh_position_offset;

out TescData
{
	vec3 position;
	vec2 uv;
	vec3 normal;
} outData;

void main(void)
{
	vec3 offset_postion = position + mesh_position_offset;
	outData.position = (model_matrix * vec4(offset_postion, 1.0f)).xyz;
	outData.uv = uv;
	outData.normal = mat3(transpose(inverse(model_matrix))) * normal;
}