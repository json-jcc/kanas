//? #version 460 core
//? #extension GL_ARB_bindless_texture : require
//? #extension GL_ARB_shading_language_include : require
//? #pragma STDGL invariant(all)
//? #pragma optimize(on)
//? #pragma debug(on)

struct PBRMaterial
{
	sampler2D albedo_map;
	sampler2D normal_map;
	sampler2D metalness_map;
	sampler2D roughness_map;
	sampler2D displacement_map;
	sampler2D ambient_occlusion_map;
};

struct PBRPointLight
{
	vec3 position;
	vec3 color;
};

struct directional_light
{
	vec3 color, direction;
};

struct point_light
{
	vec3 position, color;
	float constant, linear, quadratic;
};

struct spot_light
{
	vec3 position, color, direction;
	float cos_phy;
};

struct environment_lights
{
	vec3 ambient_light;

	directional_light[10] directional_lights;
	int directional_lights_num;

	point_light[10] point_lights;
	int point_lights_num;
	
	spot_light[10] spot_lights;
	int spot_lights_num;
};

layout(binding = 0, std140) uniform GlobalUniformBuffer
{
	PBRMaterial mat;
	PBRPointLight point_lights[4];
	vec3 camera_position;
	environment_lights en_lights;
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 projection_matrix;
	float displacement_scale;
};

layout(binding = 0, offset = 0) uniform atomic_uint xs;

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

vec2 interpolate2D(vec3 tessCoord, vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(tessCoord.x) * v0 + vec2(tessCoord.y) * v1 + vec2(tessCoord.z) * v2;
}

vec3 interpolate3D(vec3 tessCoord, vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(tessCoord.x) * v0 + vec3(tessCoord.y) * v1 + vec3(tessCoord.z) * v2;
}
