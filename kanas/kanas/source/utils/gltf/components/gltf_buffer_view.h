#ifndef GLTF_BUFFER_VIEW_H
#define GLTF_BUFFER_VIEW_H

#include "public/stl.h"
#include "public/json.h"

class gltf_buffer_view
{
public:

	gltf_buffer_view() = default;

	bool load(const nlohmann::json& object)
	{
		if (object.find("buffer") != object.cend()) object.at("buffer").get_to(_buffer);
		if (object.find("byteOffset") != object.cend()) object.at("byteOffset").get_to(_byte_offset);
		if (object.find("byteLength") != object.cend()) object.at("byteLength").get_to(_byte_length);
		if (object.find("byteStride") != object.cend()) object.at("byteStride").get_to(_byte_stride);
		if (object.find("target") != object.cend()) object.at("target").get_to(_target);

		return true;
	}

private:

	std::uint32_t _buffer;
	std::uint32_t _byte_offset;
	std::uint32_t _byte_length;
	std::uint32_t _byte_stride;
	std::uint32_t _target;

};

#endif