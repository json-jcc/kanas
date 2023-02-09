#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 mesh_position_offset;

out vec3 frag_position;
out vec2 frag_uv;
out vec3 frag_normal;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main(void)
{ 
	vec3 offset_postion = position + mesh_position_offset;

	frag_position = (model_matrix * vec4(offset_postion, 1.0f)).xyz;
	frag_uv = uv;
	frag_normal = mat3(transpose(inverse(model_matrix))) * normal;
	
	gl_Position = projection_matrix * view_matrix * vec4(frag_position, 1.0f);
}