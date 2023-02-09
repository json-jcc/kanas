#ifndef GLTF_BUFFER_H
#define GLTF_BUFFER_H

#include "public/stl.h"
#include "public/json.h"

class gltf_buffer
{
public:
	gltf_buffer() :
		_byte_length(0),
		_uri()
	{}

	~gltf_buffer() = default;

public:

	bool load(const nlohmann::json& object)
	{
		object.at("byteLength").get_to(_byte_length);
		object.at("uri").get_to(_uri);
		return true;
	}

public:

	uint32 get_byte_length() const
	{
		return _byte_length;
	}

	const std::string& get_uri() const
	{
		return _uri;
	}

private:

	uint32 _byte_length;
	std::string _uri;

};

#endif