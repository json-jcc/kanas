#ifndef GLTF_TEXTURE_H
#define GLTF_TEXTURE_H

#include "gltf_sampler.h"
#include "gltf_image.h"

class gltf_texture
{
public:

	bool load(const nlohmann::json& object)
	{
		return true;
	}

private:

	std::vector<gltf_image*> _images;
	std::vector<gltf_sampler*> _samplers;


};

#endif