#version 460 core
#extension GL_ARB_bindless_texture : require

struct Material
{
	vec3 baseColor;
	sampler2D albedoSamp;
	sampler2D roughnessSamp;
	sampler2DRect rescl;
};

layout(binding = 0, std140) uniform GlobalUniformBuffer
{
	vec4 validationPosition;
	sampler2D albedoMap;
	sampler2DArray albedoMaps;
	sampler2DArrayShadow shadowAlbedoMaps;
};

layout(binding = 0, std430) buffer GlobalBuffer
{
	vec4 aa;
	layout(r32f) image1D readBackPosition1;
};

layout(binding = 0, offset = 0) uniform atomic_uint xs;


layout(location = 0) in vec3 att0;
layout(location = 1) in vec4 att1;
layout(location = 2) in vec4 att2;

layout(location = 0) out vec4 color0;
layout(location = 1) out vec4 color1;
layout(location = 2) out vec4 color2;

// texture, textureOffset, 
// textureLod, textureLodOffset,
// textureGather, textureGatherOffset, textureGatherOffsets, 
// textureGrad, textureGradOffset,
// 
// textureProj, textureProjOffset
// textureProjLod, textureProjLodOffset, 
// textureProjGrad, textureProjGrad, textureProjGradOffset,
//
// textureSamples
// textureSize

// imageLoad
// imageStore
// imageSamples
// imageSize
// imageAtomicAdd
// imageAtomicAnd
// imageAtomicCompSwap
// imageAtomicExchange
// imageAtomicMax
// imageAtomicMin
// imageAtomicOr
// imageAtomicXor

// texelFetch, 
//
//
//
void main()
{
	vec4 albedoColor0 = texture(albedoMap, vec2(1, 2));
	vec4 albedoColor1 = texture(albedoMaps, vec3(1, 2, 2));
	float shadowColor = texture(shadowAlbedoMaps, vec4(1, 1, 1, 1));
	aa = vec4(0);
}