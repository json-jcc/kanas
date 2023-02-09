#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_shading_language_include : require
#pragma STDGL invariant(all)
#pragma optimize(on)
#pragma debug(on)
#include "/common.glsl" //! #include "../../templates/common.glsl"

//-------------------------------------------------------
layout(triangles, equal_spacing, ccw) in;

 in TeseData
 {
	vec3 position;
	vec2 uv;
	vec3 normal;
 } inData[];

 out GeomData
 {
	vec3 position;
	vec2 uv;
	vec3 normal;
	float disp;
 } outData;

void main(void)
{
	outData.position = interpolate3D(gl_TessCoord, inData[0].position, inData[1].position, inData[2].position);
	outData.uv = interpolate2D(gl_TessCoord, inData[0].uv, inData[1].uv, inData[2].uv);
	outData.normal = normalize(interpolate3D(gl_TessCoord, inData[0].normal, inData[1].normal, inData[2].normal));
	
	float displacement = texture(mat.displacement_map, outData.uv).r;
	outData.position += outData.normal * displacement * 0.05f;
	
	outData.disp = displacement;

	gl_Position = projection_matrix * view_matrix * vec4(outData.position, 1.0f);
}



