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

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

//-------------------------------------------------------
layout(triangles, equal_spacing, ccw) in;

in vec3 tese_position[];
in vec2 tese_uv[];
in vec3 tese_normal[];

out vec3 gs_position;
out vec2 gs_uv;
out vec3 gs_normal;
out float gs_disp;

uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform float displacement_scale;
uniform PBRMaterial mat;

void main(void)
{
	gs_position = interpolate3D(tese_position[0], tese_position[1], tese_position[2]);
	gs_uv = interpolate2D(tese_uv[0], tese_uv[1], tese_uv[2]);
	gs_normal = normalize(interpolate3D(tese_normal[0], tese_normal[1], tese_normal[2]));
	
	float displacement = texture(mat.displacement_map, gs_uv).r;
	gs_position += gs_normal * displacement * 0.05f;
	
	gs_disp = displacement;

	gl_Position = projection_matrix * view_matrix * vec4(gs_position, 1.0f);
}



