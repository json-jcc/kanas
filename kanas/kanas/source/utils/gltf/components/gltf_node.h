#ifndef GLTF_NODE_H
#define GLTF_NODE_H

#include "public/glm.h"
#include "gltf_camera.h"
#include "gltf_mesh.h"
#include "gltf_skin.h"

class gltf_node
{
public:
    gltf_node()
    {

    }

public:
    
    bool load(const nlohmann::json& object)
    {
        return true;
    }

public:

    glm::mat4 matrix; // M = T * R * S
    std::string m;

    glm::vec3 translation;
    glm::vec4 rotation;
    glm::vec3 scale;

    gltf_mesh* _mesh;
    gltf_camera* _camera;

};

void to_json(nlohmann::json& j, const gltf_node& n) {
    //j = json{ {"name", p.name}, {"address", p.address}, {"age", p.age} };
}

void from_json(const nlohmann::json& j, gltf_node& n) {
    j.at("matrix").get_to(n.m);
    j.at("mesh");
    j.at("camera");
}

#endif