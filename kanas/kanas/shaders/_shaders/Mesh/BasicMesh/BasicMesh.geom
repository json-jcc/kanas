#version 450 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 gs_position[];
in vec3 gs_color[];
in vec3 gs_normal[];
in vec2 gs_texture_coords[];

out vec3 frag_position;
out vec3 frag_color;
out vec3 frag_normal;
out vec2 frag_texture_coords;

void main()
{
	for(int i = 0; i < 3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		frag_position = gs_position[i];
		frag_normal = gs_normal[i];
		frag_texture_coords = gs_texture_coords[i];
		frag_color = gs_color[i];

		EmitVertex();
	}
	EndPrimitive();
}
