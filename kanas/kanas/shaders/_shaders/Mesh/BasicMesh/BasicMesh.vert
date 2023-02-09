#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 texture_coords;
layout(location = 4) in vec3 mesh_position_offset;

out vec3 tesc_position;
out vec3 tesc_color;
out vec3 tesc_normal;
out vec2 tesc_texture_coords;

uniform mat4 model_matrix;

void main(void)
{
	vec3 offset_postion = position + mesh_position_offset;

	tesc_position = (model_matrix * vec4(offset_postion, 1.0f)).xyz;
	tesc_normal = mat3(transpose(inverse(model_matrix))) * normal;
	tesc_texture_coords = texture_coords;
	tesc_color = color;
	
}