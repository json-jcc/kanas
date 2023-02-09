#version 450 core

struct material
{
	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;

	float shininess;
	float opacity;

	sampler2D[10] ambient_maps;
	int ambient_maps_num;
	sampler2D[10] diffuse_maps;
	int diffuse_maps_num;
	sampler2D[10] specular_maps;
	int specular_maps_num;
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