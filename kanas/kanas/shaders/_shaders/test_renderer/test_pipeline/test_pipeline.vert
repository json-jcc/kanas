#version 450 core

struct PBRMaterial
{
	sampler2D albedo_map;
	sampler2D normal_map;
	sampler2D metalness_map;
	sampler2D roughness_map;
	sampler2D displacement_map;
	sampler2D ambient_occlusion_map;
};

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 mesh_position_offset;

uniform mat4 model_matrix;
uniform PBRMaterial mat;

out vec3 tesc_position;
out vec2 tesc_uv;
out vec3 tesc_normal;

void main(void)
{
	vec3 offset_postion = position + mesh_position_offset;
	tesc_position = (model_matrix * vec4(offset_postion, 1.0f)).xyz;
	tesc_uv = uv;
	tesc_normal = mat3(transpose(inverse(model_matrix))) * normal;
}