#ifndef GLTF_CAMERA_H
#define GLTF_CAMERA_H

#include "public/stl.h"
#include "public/json.h"

class gltf_camera
{
public:
	bool load(const nlohmann::json& object)
	{
		return true;
	}

};

#endif