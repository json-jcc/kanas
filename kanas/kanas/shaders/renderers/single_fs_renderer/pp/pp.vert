#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_shading_language_include : require
#extension GL_KHR_vulkan_glsl : require
#pragma STDGL invariant(all)
#pragma optimize(on)
#pragma debug(on)

const vec2 quad_vertices[4] = vec2[4]( vec2( -1.0, -1.0), vec2( 1.0, -1.0), vec2( -1.0, 1.0), vec2( 1.0, 1.0));

layout(set=1, binding = 0) uniform sampler mySampler; //sampler
//layout(set=1, binding = 1) uniform texture2D mySampledImage; // sampledImage
layout(set=1, binding = 1) uniform sampler2D myCombinedImageSampler; // combinedImageSampler
//layout(set=1, binding = 1) uniform textureBuffer myUniformTexBuffer; // uniformTexelBuffer
layout(set=1, binding = 1, r32f) uniform imageBuffer myStorageTexelBuffer; // storageTexelBuffer


layout (input_attachment_index=0, set=0, binding=1) uniform usubpassInput myInput;

void main()
{
    gl_VertexIndex;
    gl_Position = vec4(quad_vertices[gl_VertexID], 0.0, 1.0);
}