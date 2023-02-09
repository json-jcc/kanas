#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_shading_language_include : require
#pragma STDGL invariant(all)
#pragma optimize(on)
#pragma debug(on)


layout(location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}