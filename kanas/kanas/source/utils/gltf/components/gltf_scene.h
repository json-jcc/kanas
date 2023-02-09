#ifndef GLTF_SCENE_H
#define GLTF_SCENE_H

#include "public/stl.h"
#include "public/json.h"

class gltf_scene
{
public:

	bool load(const nlohmann::json& object)
	{
		return true;
	}

private:

	std::string _name;
	std::vector<uint32> _nodes;
	
};

#endif