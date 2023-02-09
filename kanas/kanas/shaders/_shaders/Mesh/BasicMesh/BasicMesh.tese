#version 450 core

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
in vec3 tese_color[];
in vec3 tese_normal[];
in vec2 tese_texture_coords[];

out vec3 gs_position;
out vec3 gs_color;
out vec3 gs_normal;
out vec2 gs_texture_coords;

uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main(void)
{
	gs_texture_coords = interpolate2D(tese_texture_coords[0], tese_texture_coords[1], tese_texture_coords[2]);
	gs_normal = normalize(interpolate3D(tese_normal[0], tese_normal[1], tese_normal[2]));
	gs_position = interpolate3D(tese_position[0], tese_position[1], tese_position[2]);
	gs_color = tese_color[0];
	
	gl_Position = projection_matrix * view_matrix * vec4(gs_position, 1.0f);
}



