#version 450 core

float GetTessLevel(float Distance0, float Distance1)
{
	float AvgDistance = (Distance0 + Distance1) / 2;
	if(AvgDistance <= 2.0)
	{
		return 10.0;
	}
	else if(AvgDistance <= 5.0)
	{
		return 7.0;
	}
	else
	{
		return 3.0;
	}
}

//----------------------------
layout(vertices = 3) out;

uniform vec3 camera_position;

in vec3 tesc_position[];
in vec3 tesc_color[];
in vec3 tesc_normal[];
in vec2 tesc_texture_coords[];

out vec3 tese_position[];
out vec3 tese_color[];
out vec3 tese_normal[];
out vec2 tese_texture_coords[];

void main()
{
	tese_position[gl_InvocationID] = tesc_position[gl_InvocationID];
	tese_normal[gl_InvocationID] = tesc_normal[gl_InvocationID];
	tese_texture_coords[gl_InvocationID] = tesc_texture_coords[gl_InvocationID];
	tese_color[gl_InvocationID] = tesc_color[gl_InvocationID];

	float Distance0 = distance(camera_position, tesc_position[0]); 
	float Distance1 = distance(camera_position, tesc_position[1]); 
	float Distance2 = distance(camera_position, tesc_position[2]); 

	if (gl_InvocationID == 0)
	{
		
		gl_TessLevelOuter[0] = GetTessLevel(Distance1, Distance2);
		gl_TessLevelOuter[1] = GetTessLevel(Distance2, Distance0);
		gl_TessLevelOuter[2] = GetTessLevel(Distance0, Distance1);

		gl_TessLevelInner[0] = gl_TessLevelOuter[2];
	}
}



