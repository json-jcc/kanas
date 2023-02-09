#ifndef GLTF_ASSET_H
#define GLTF_ASSET_H

#include "public/stl.h"
#include "public/json.h"

class gltf_asset
{
public:
	gltf_asset()
	{

	}

	~gltf_asset() = default;

public:

	bool load(const nlohmann::json& object)
	{
		return true;
	}

};


#endif