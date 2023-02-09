#ifndef GLTF_FILE_H
#define GLTF_FILE_H

#include "gltf_scene.h"
#include "gltf_asset.h"
#include "gltf_node.h"
#include "gltf_camera.h"
#include "gltf_mesh.h"
#include "gltf_image.h"
#include "gltf_material.h"
#include "gltf_sampler.h"
#include "gltf_texture.h"
#include "gltf_accessor.h"
#include "gltf_buffer.h"
#include "gltf_buffer_view.h"
#include "gltf_animation.h"
#include "gltf_skin.h"

class gltf_file
{
public:
	gltf_file() = default;

	~gltf_file() = default;

public:

	bool load(const std::string& path)
	{
		std::string _scene_gltf_path = path + "\\*.gltf";
		if (!std::filesystem::exists(path))  return false;

		nlohmann::json _file;
		std::ifstream(_scene_gltf_path) >> _file;

		auto _obj = _file.object();
		if (_file.find("")!= _file.end())
		{
			_asset = new gltf_asset();
		}
		uint32 index = _file.at("scene");
		if (_file.find("scenes") != _file.end())
		{
			auto _scene_objs = _file.at("scenes");
			for (auto _it = _scene_objs.cbegin(); _it != _scene_objs.cend(); ++_it)
			{
				auto _scene = new gltf_scene();
				if (_scene && _scene->load(*_it)) _scenes.push_back(_scene);
			}
		}
		if (_file.find("nodes") != _file.end())
		{
			auto _node_objs = _file.at("nodes");
			for (auto _it = _node_objs.cbegin(); _it != _node_objs.cend(); ++_it)
			{
				auto _nod = new gltf_node();
				if (_nod && _nod->load(*_it)) _nodes.push_back(_nod);
			}
		}
		if (_file.find("cameras") != _file.end())
		{
			auto _camera_objs = _file.at("cameras");
			for (auto _it = _camera_objs.cbegin(); _it != _camera_objs.cend(); ++_it)
			{
				auto _cam = new gltf_camera();
				if (_cam && _cam->load(*_it)) _cameras.push_back(_cam);
			}
		}
		if (_file.find("meshes") != _file.end())
		{
			auto _meshe_objs = _file.at("meshes");
			for (auto _it = _meshe_objs.cbegin(); _it != _meshe_objs.cend(); ++_it)
			{
				auto _mesh = new gltf_mesh();
				if (_mesh && _mesh->load(*_it)) _meshes.push_back(_mesh);
			}
		}
		if(_file.find("materials") != _file.end())
		{
			auto _mat_objs = _file.at("materials");
			for (auto _it = _mat_objs.cbegin(); _it != _mat_objs.cend(); ++_it)
			{
				auto _mat = new gltf_material();
				if (_mat && _mat->load(*_it)) _materials.push_back(_mat);
			}
		}
		if (_file.find("textures") != _file.end())
		{
			auto _texture_objs = _file.at("textures");
			for (auto _it = _texture_objs.cbegin(); _it != _texture_objs.cend(); ++_it)
			{
				auto _tex = new gltf_texture();
				if (_tex && _tex->load(*_it)) _textures.push_back(_tex);
			}
		}
		if (_file.find("samplers") != _file.end())
		{
			auto _sampler_objs = _file.at("samplers");
			for (auto _it = _sampler_objs.cbegin(); _it != _sampler_objs.cend(); ++_it)
			{
				auto _smp = new gltf_sampler();
				if (_smp && _smp->load(*_it)) _samplers.push_back(_smp);
			}
		}
		if (_file.find("images") != _file.end())
		{
			auto _image_objs = _file.at("images");
			for (auto _it = _image_objs.cbegin(); _it != _image_objs.cend(); ++_it)
			{
				auto _img = new gltf_image();
				if (_img && _img->load(*_it)) _images.push_back(_img);
			}
		}
		if (_file.find("accessors") != _file.end())
		{
			auto _accessor_objs = _file.at("accessors");
			for (auto _it = _accessor_objs.cbegin(); _it != _accessor_objs.cend(); ++_it)
			{
				auto _acc = new gltf_accessor();
				if (_acc && _acc->load(*_it)) _accessors.push_back(_acc);
			}
		}
		if (_file.find("buffers") != _file.end())
		{
			auto _buffer_objs = _file.at("buffers");
			for (auto _it = _buffer_objs.cbegin(); _it != _buffer_objs.cend(); ++_it)
			{
				auto _buf = new gltf_buffer();
				if (_buf && _buf->load(*_it)) _buffers.push_back(_buf);
			}
		}
		if (_file.find("bufferViews") != _file.end())
		{
			auto _buffer_view_objs = _file.at("bufferViews");
			for (auto _it = _buffer_view_objs.cbegin(); _it != _buffer_view_objs.cend(); ++_it)
			{
				auto _buf_view = new gltf_buffer_view();
				if (_buf_view && _buf_view->load(*_it)) _buffer_views.push_back(_buf_view);
			}
		}
		return true;
	}

public:
	gltf_asset* asset() const { return _asset; }
	uint32 scene_index() const { return _scene; }
	const auto& scenes() const { return _scenes; }
	const auto& nodes() const { return _nodes; }
	const auto& cameras() const { return _cameras; }
	const auto& meshes() const { return _meshes; }
	const auto& accessors() const { return _accessors; }
	const auto& textures() const { return _textures; }
	const auto& images() const { return _images; }
	const auto& samplers() const { return _samplers; }
	const auto& materials() const { return _materials; }
	const auto& buffers() const { return _buffers; }
	const auto& buffer_views() const { return _buffer_views; }

private:
	
	uint32 _scene;
	gltf_asset* _asset;
	std::vector<gltf_scene*> _scenes;
	std::vector<gltf_node*> _nodes;
	std::vector<gltf_camera*> _cameras;
	std::vector<gltf_mesh*> _meshes;
	std::vector<gltf_accessor*> _accessors;
	std::vector<gltf_texture*> _textures;
	std::vector<gltf_image*> _images;
	std::vector<gltf_sampler*> _samplers;
	std::vector<gltf_material*> _materials;
	std::vector<gltf_buffer*> _buffers;
	std::vector<gltf_buffer_view*> _buffer_views;

};

#endif