#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 TexCoord;
layout(location = 2) flat in ivec4 test;
layout(location = 3) in vec4 _color;
layout(location = 4) in vec4 _text;

out vec4 FragColor;

uniform sampler2D container2;
uniform sampler2D container3;

uniform vec3 camera_position;
uniform vec4 spe_color;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;



layout(shared) uniform Block0
{
	vec4 color0;
	vec4 position0;
};

layout(shared) uniform Block1
{
	vec4 color1;
	vec4 position1;
};

layout(shared) uniform Block2
{
	vec4 color2;
	vec4 position2;
};




void main()
{

	lowp float a = texture(container3, TexCoord).r;

	FragColor = color0;
}

