#version 450 core

float GetTessLevel(float distance0, float distance1);

//----------------------------
layout(vertices = 3) out;

in vec3 tesc_position[];
in vec2 tesc_uv[];
in vec3 tesc_normal[];

out vec3 tese_position[];
out vec2 tese_uv[];
out vec3 tese_normal[];

uniform vec3 camera_position;

void main()
{
	tese_position[gl_InvocationID] = tesc_position[gl_InvocationID];
	tese_normal[gl_InvocationID] = tesc_normal[gl_InvocationID];
	tese_uv[gl_InvocationID] = tesc_uv[gl_InvocationID];

	float distance0 = distance(camera_position, tesc_position[0]); 
	float distance1 = distance(camera_position, tesc_position[1]); 
	float distance2 = distance(camera_position, tesc_position[2]); 

	if (gl_InvocationID == 0)
	{
		gl_TessLevelOuter[0] = GetTessLevel(distance1, distance2);
		gl_TessLevelOuter[1] = GetTessLevel(distance2, distance0);
		gl_TessLevelOuter[2] = GetTessLevel(distance0,distance1);

		gl_TessLevelInner[0] = gl_TessLevelOuter[2];
	}
}


float GetTessLevel(float distance0, float distance1)
{
	float avg_distance = (distance0 + distance1) / 2;
	// if(avg_distance <= 2.0)
	// {
	// 	return 100.0;
	// }
	// else if(avg_distance <= 5.0)
	// {
	// 	return 7.0;
	// }
	// else
	// {
	// 	return 3.0;
	// }

	return 100;
}

