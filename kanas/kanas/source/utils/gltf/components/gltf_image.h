#ifndef GLTF_IMAGE_H
#define GLTF_IMAGE_H

#include "public/stl.h"
#include "public/json.h"

class gltf_image
{
public:

	gltf_image()
	{}

	bool load(const nlohmann::json& object)
	{
		if (object.find("uri") != object.cend()) object.at("uri").get_to(_uri);
		return true;
	}

private:

	std::string _uri; // "uri"

	uint32 _buffer_view; // "bufferView"
	std::string _mime_type; // "mimeType"

};

#endif