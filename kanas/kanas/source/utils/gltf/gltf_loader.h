#ifndef GLTF_LOADER_H
#define GLTF_LOADER_H

#include "components/gltf_file.h"

class gltf_loader
{
public:

	static std::shared_ptr<gltf_file> load(const std::string& path)
	{
		return nullptr;
	}

	static std::vector<std::shared_ptr<gltf_file>> load(const std::vector<std::string>& path)
	{
		std::vector<std::shared_ptr<gltf_file>> _files;
		return _files;
	}

};

#endif