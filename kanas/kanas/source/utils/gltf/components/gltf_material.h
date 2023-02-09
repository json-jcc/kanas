#ifndef GLTF_MATERIAL_H
#define GLTF_MATERIAL_H

#include "gltf_texture.h"

class gltf_material
{
public:
	bool load(const nlohmann::json& object)
	{
		return true;
	}

private:

	std::uint32_t _base_color_texture_index;
	std::uint32_t _base_color_texture_tex_coord;
	glm::vec4 _base_color_factor;
	std::uint32_t _metallic_roughness_texture_index;
	std::uint32_t _metallic_roughness_texture_tex_coord;
	float _metallic_factor;
	float _roughness_factor;

	std::uint32_t _normal_tex_scale;
	std::uint32_t _normal_tex_index;
	std::uint32_t _normal_tex_coord;

	std::uint32_t _occlusion_tex_strength;
	std::uint32_t _occlusion_tex_index;
	std::uint32_t _occlusion_tex_coord;

	std::uint32_t _emissive_tex_index;
	std::uint32_t _emissive_tex_coord;

	glm::vec3 _emissive_factor;



};

#endif