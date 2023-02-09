#ifndef GLTF_ACCESSOR_H
#define GLTF_ACCESSOR_H

#include "public/stl.h"
#include "public/json.h"

class gltf_accessor
{
public:
	gltf_accessor() = default;

	~gltf_accessor() = default;

public:

	bool load(const nlohmann::json& object)
	{
		
		return true;
	}

private:

	uint32 _buffer_view;
	uint32 _byte_offset;
	std::string _type;
	uint32 _component_type;
	uint32 _count;
	glm::vec2 _min;
	glm::vec2 _max;

};

#endif