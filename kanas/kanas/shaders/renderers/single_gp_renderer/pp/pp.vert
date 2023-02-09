#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_shading_language_include : require
#pragma STDGL invariant(all)
#pragma optimize(on)
#pragma debug(on)

layout(location = 0) in vec3 position;

void main()
{
	gl_Position = vec4(position.x, position.y, position.z, 1.0f);
}