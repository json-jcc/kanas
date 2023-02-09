#version 460 core

#ifndef IMMUTABLE_PARAMETERS
#define IMMUTABLE_PARAMETERS

struct Matrices
{
	vec3 a;
	vec2 v;
};

layout(location=0) in vec3 position;
layout(location=1) in vec2 uv;
layout(location=2) in ivec4 instance_test;

layout(std140) uniform GlobalBlock
{
	Matrices x[10];

} GlobalBlockInstance;

layout(std430) buffer stt
{
	vec2 assx;
} ast;

layout(binding = 0, r32f, location = 1) writeonly uniform image1D positionImage1D;
layout(binding = 0, r32f, location = 2) coherent restrict uniform image1DArray normalImage1Ds;
layout(binding = 0, offset = 4) uniform atomic_uint counter;
layout(binding = 0, offset = 8) uniform atomic_uint counter1;
layout(binding = 0) uniform sampler2DArray ass;
layout(binding = 0) uniform sampler2DArray ass1;
#endif

out VertexData
{
  vec3 color;
  vec2 texCoord;
} outData;


void main()
{
	GlobalBlockInstance.x[0];
	imageLoad(normalImage1Ds, ivec2(0, 0));
	outData.color = vec3(1.0f);
}

