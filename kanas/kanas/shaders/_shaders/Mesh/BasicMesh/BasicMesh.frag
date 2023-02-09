#version 450 core
#define MAX_NUM_LIGHT 100

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



// --------------------
vec3 caculate_mat_ambient_color(material mat, vec2 texture_coords)
{
	vec3 mat_ambient_color;
	for(int i = 0; i < mat.ambient_maps_num; i++)
	{
		mat_ambient_color += texture(mat.ambient_maps[i], texture_coords).rgb;
	}
	mat_ambient_color += mat.ambient_color;

	return mat_ambient_color;
}

vec3 caculate_mat_diffuse_color(material mat, vec2 texture_coords)
{
	vec3 mat_diffuse_color;
	for(int i = 0; i < mat.diffuse_maps_num; i++)
	{
		mat_diffuse_color += texture(mat.diffuse_maps[i], texture_coords).rgb;
	}
	mat_diffuse_color += mat.diffuse_color;

	return mat_diffuse_color;
}

vec3 caculate_mat_specular_color(material mat, vec2 texture_coords)
{
	vec3 mat_specular_color;
	for(int i = 0; i < mat.specular_maps_num; i++)
	{
		mat_specular_color += texture(mat.specular_maps[i], texture_coords).rgb;
	}
	mat_specular_color += mat.specular_color;

	return mat_specular_color;
}

float diffuse_factor(vec3 light_direction, vec3 normal)
{
	return max(dot(light_direction, normal), 0);
}

float specular_factor(vec3 light_reflect_direction, vec3 view_direction, float shininess)
{
	return pow(max(dot(view_direction, light_reflect_direction), 0), shininess);
}

vec3 caculate_directional_lights_diffuse_effect(vec3 normal, vec3 view_direction,  environment_lights lights, material mat)
{
	vec3 diffuse_effect;
	for(int i = 0; i < lights.directional_lights_num; i++)
	{
		vec3 direction = lights.directional_lights[i].direction;
		vec3 color = lights.directional_lights[i].color;

		vec3 reflect_direction = reflect(direction, normal);

		diffuse_effect += color * diffuse_factor(direction, normal);
	}
	return diffuse_effect;
}

vec3 caculate_directional_lights_specular_effect(vec3 normal, vec3 view_direction,  environment_lights lights, material mat)
{
	vec3 specular_effect;
	for(int i = 0; i < lights.directional_lights_num; i++)
	{
		vec3 direction = lights.directional_lights[i].direction;
		vec3 color = lights.directional_lights[i].color;

		vec3 reflect_direction = reflect(direction, normal);

		specular_effect += color * specular_factor(reflect_direction, view_direction, mat.shininess);
	}
	return specular_effect;
}

vec3 caculate_point_lights_diffuse_effect(vec3 normal, vec3 view_direction, vec3 frag_position, environment_lights lights, material mat)
{
	vec3 diffuse_effect;
	for(int i = 0; i < lights.point_lights_num; i++)
	{
		vec3 color = lights.point_lights[i].color;
		vec3 position = lights.point_lights[i].position;
		float constant = lights.point_lights[i].constant;
		float linear = lights.point_lights[i].linear;
		float quadratic = lights.point_lights[i].quadratic;

		float source_distance = length(position - frag_position);
		float attenuation = 1.0f / (constant + linear * source_distance + quadratic * pow(source_distance, 2));
		vec3 direction = normalize(frag_position - position); 
		vec3 reflect_direction = reflect(direction, normal);

		diffuse_effect += attenuation * color * diffuse_factor(direction, normal);
	}
	return diffuse_effect;
}

vec3 caculate_point_lights_specular_effect(vec3 normal, vec3 view_direction, vec3 frag_position, environment_lights lights, material mat)
{
	vec3 specular_effect;
	for(int i = 0; i < lights.point_lights_num; i++)
	{
		vec3 color = lights.point_lights[i].color;
		vec3 position = lights.point_lights[i].position;
		float constant = lights.point_lights[i].constant;
		float linear = lights.point_lights[i].linear;
		float quadratic = lights.point_lights[i].quadratic;

		float source_distance = length(position - frag_position);
		float attenuation = 1.0f / (constant + linear * source_distance + quadratic * pow(source_distance, 2));
		vec3 direction = normalize(frag_position - position); 
		vec3 reflect_direction = reflect(direction, normal);

		specular_effect += color * specular_factor(reflect_direction, view_direction, mat.shininess);
	}
	return specular_effect;
}

vec3 caculate_spot_lights_diffuse_effect(vec3 normal, vec3 view_direction, vec3 frag_position, environment_lights lights, material mat)
{
	vec3 diffuse_effect;
	for(int i = 0; i < lights.spot_lights_num; i++)
	{
		vec3 color = lights.spot_lights[i].color;
		vec3 position = lights.spot_lights[i].position;
		vec3 direction = lights.spot_lights[i].direction;
		float cos_phy = lights.spot_lights[i].cos_phy;

		vec3 reflect_direction = reflect(direction, normal);
		float cos_theta = dot(normalize(frag_position - position), -direction);
		if(cos_phy < cos_theta)
		{
			diffuse_effect += color * diffuse_factor(direction, normal);
		}
	}
	return diffuse_effect;
}

vec3 caculate_spot_lights_specular_effect(vec3 normal, vec3 view_direction, vec3 frag_position, environment_lights lights, material mat)
{
	vec3 specular_effect;
	for(int i = 0; i < lights.spot_lights_num; i++)
	{
		vec3 color = lights.spot_lights[i].color;
		vec3 position = lights.spot_lights[i].position;
		vec3 direction = lights.spot_lights[i].direction;
		float cos_phy = lights.spot_lights[i].cos_phy;

		vec3 reflect_direction = reflect(direction, normal);
		float cos_theta = dot(normalize(frag_position - position), -direction);
		if(cos_phy < cos_theta)
		{
			specular_effect += color * specular_factor(reflect_direction, view_direction, mat.shininess);
		}
	}
	return specular_effect;
}

// ---------------------------------------------
vec3 caculate_mat_ambient_color(material mat, vec2 texture_coords);
vec3 caculate_mat_diffuse_color(material mat, vec2 texture_coords);
vec3 caculate_mat_specular_color(material mat, vec2 texture_coords);

float ambient_factor();
float diffuse_factor(vec3 _light_direction, vec3 _normal);
float specular_factor(vec3 _light_reflect_direction, vec3 _view_direction, float _shininess);

// ----------------------------------------
in vec3 frag_position;
in vec3 frag_color;
in vec3 frag_normal;
in vec2 frag_texture_coords;

uniform vec3 camera_position;
uniform material mat;
uniform environment_lights en_lights;

out vec4 fragment_color;

void main(void)
{
	vec3 view_direction = normalize(frag_position - camera_position);
	vec3 ambient_effect, diffuse_effect, specular_effect;
	vec3 ambient_color, diffuse_color, specular_color;

	diffuse_effect += caculate_directional_lights_diffuse_effect(frag_normal, view_direction, en_lights, mat);
	specular_effect += caculate_directional_lights_specular_effect(frag_normal, view_direction, en_lights, mat);
	diffuse_effect += caculate_point_lights_diffuse_effect(frag_normal, view_direction, frag_position,  en_lights, mat);
	specular_effect += caculate_point_lights_specular_effect(frag_normal, view_direction, frag_position,  en_lights, mat);
	diffuse_effect += caculate_spot_lights_diffuse_effect(frag_normal, view_direction, frag_position, en_lights, mat);
	specular_effect += caculate_spot_lights_specular_effect(frag_normal, view_direction, frag_position, en_lights, mat);

	ambient_color += caculate_mat_ambient_color(mat, frag_texture_coords) * en_lights.ambient_light;
	diffuse_color += caculate_mat_diffuse_color(mat, frag_texture_coords) * diffuse_effect;
	specular_color += caculate_mat_specular_color(mat, frag_texture_coords) * specular_effect;
	
	fragment_color = vec4(ambient_color + diffuse_color + specular_color, 1.0f);
}