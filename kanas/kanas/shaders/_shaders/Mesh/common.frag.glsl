//? #version 460 core
//? #extension GL_ARB_bindless_texture : require
//? #extension GL_ARB_shading_language_include : require
//? #pragma STDGL invariant(all)
//? #pragma optimize(on)
//? #pragma debug(on)


// calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
// of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow) 

// Cook-Torrance reflectance equation - BRDF
		// f r = (kd) * (f lambert) + (ks) * (f cook-torrance)
		// kd = 1 - ks
		// f lambert = color / PI
		// f cook-torrance = DFG / 4 * (view_direc * normal)(light_direc * normal)

// ----------------------------------------------------------------------------
// Easy trick to get tangent-normals to world-space to keep PBR code simplified.
// Don't worry if you don't get what's going on; you generally want to do normal 
// mapping the usual way for performance anways; I do plan make a note of this 
// technique somewhere later in the normal mapping tutorial.

const float PI = 3.14159265359;
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}
// ----------------------------------------------------------------------------

vec3 GetNormalFromMap(vec3 normal, sampler2D normal_map, vec2 uv, vec3 f_position)
{
	 vec3 tangent_normal = texture(normal_map, uv).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(f_position);
    vec3 Q2  = dFdy(f_position);
    vec2 st1 = dFdx(uv);
    vec2 st2 = dFdy(uv);

    vec3 N   = normalize(normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

	return normalize(TBN * tangent_normal);
}