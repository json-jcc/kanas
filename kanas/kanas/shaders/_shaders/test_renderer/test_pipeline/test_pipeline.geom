#version 450 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 gs_position[];
in vec2 gs_uv[];
in vec3 gs_normal[];
in float gs_disp[];

out vec3 frag_position;
out vec2 frag_uv;
out vec3 frag_normal;
out float frag_disp;

void main()
{
	for(int i = 0; i < 3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		frag_position = gs_position[i];
		frag_uv = gs_uv[i];
		frag_normal = gs_normal[i];
		frag_disp = gs_disp[i];		
		EmitVertex();
	}
	EndPrimitive();
}
