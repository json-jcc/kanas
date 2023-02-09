#version 450 core

struct PBRMaterial
{
	sampler2D albedo_map;
	sampler2D normal_map;
	sampler2D metalness_map;
	sampler2D roughness_map;
	sampler2D displacement_map;
	sampler2D ambient_occlusion_map;
};

struct PBRPointLight
{
	vec3 position;
	vec3 color;
};

struct directional_light
{
	vec3 color, direction;
};

struct point_light
{
	vec3 position, color;
	float constant, linear, quadratic;
};

struct spot_light
{
	vec3 position, color, direction;
	float cos_phy;
};

struct environment_lights
{
	vec3 ambient_light;

	directional_light[10] directional_lights;
	int directional_lights_num;

	point_light[10] point_lights;
	int point_lights_num;
	
	spot_light[10] spot_lights;
	int spot_lights_num;
};

float DistributionGGX(vec3 N, vec3 H, float roughness); 
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
vec3 fresnelSchlick(float cosTheta, vec3 F0);
vec3 GetNormalFromMap(vec3 normal, sampler2D normal_map, vec2 uv, vec3 frag_position);

in vec3 frag_position;
in vec2 frag_uv;
in vec3 frag_normal;
in float frag_disp;

out vec4 final_frag_color;

uniform PBRMaterial mat;
uniform PBRPointLight point_lights[4];
uniform vec3 camera_position;
uniform environment_lights en_lights;

const float PI = 3.14159265359;

void main()
{
	vec3 N = GetNormalFromMap(frag_normal, mat.normal_map, frag_uv, frag_position);

	vec3 albedo = pow(texture(mat.albedo_map, frag_uv).rgb, vec3(2.2));
	float metalness = texture(mat.metalness_map, frag_uv).r;
	float roughness = texture(mat.roughness_map, frag_uv).r;
	float ambient_occlusion = texture(mat.ambient_occlusion_map, frag_uv).r;

	vec3 V = normalize(camera_position - frag_position);
	
	vec3 F0 = vec3(0.04f); // F0 (1-metalness) + albedo*metalness 
	F0 = mix(F0, albedo, metalness); // base reflectivity of the surface

	vec3 Lo = vec3(0.0f);

	for(int i = 0; i < en_lights.point_lights_num; ++i)
	{
		point_light light = en_lights.point_lights[i];

		float light_distance = length(light.position - frag_position);
		float attenuation = 1.0f / (light.constant + light.linear * light_distance + light.quadratic * pow(light_distance, 2)); //float attenuation = 1.0 / (light_distance * light_distance);
		
		vec3 radiance = light.color * attenuation;

		vec3 L = normalize(light.position - frag_position);
		vec3 H = normalize(V + L);

        float D = DistributionGGX(N, H, roughness); 
        float G = GeometrySmith(N, V, L, roughness); 
        vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0); 
        
		//vec3 numerator = D * G * F;
        //float denominator = 4 * max(dot(V, N), 0.0f) * max(dot(L, N), 0.0f); 
        //vec3 specular = numerator / max(0.001f, denominator); // 0.001 to prevent divide by zero.
        
        // kS is equal to Fresnel
        vec3 Ks = F; // 直接反射的光
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 Kd = vec3(1.0) - Ks; //进入表面的光（吸收/射出-漫反射）
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals have no diffuse light).
        Kd *= 1.0 - metalness; //纯金属，进入表面的光会被完全吸收，不会具有漫反射效应

        float NdotL = max(dot(N, L), 0.0f);// scale light by NdotL cosTheta
		float NdotV = max(dot(N, V), 0.0f);

		// do as formula
		vec3 fr = Kd * ( albedo / PI ) + Ks * ( D * G * F ) / max((4 * NdotV * NdotL), 0.001f); 
		vec3 Li = radiance;
		Lo += fr * Li * NdotL;

        // add to outgoing radiance Lo
        //Lo += (Kd * albedo / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
	}

	vec3 ambient = albedo * ambient_occlusion * vec3(0.03f); 
	vec3 frag_color = ambient + Lo;
	
	frag_color = frag_color / (frag_color + vec3(1.0f)); // HDR Tone Mapping
	// Gamma Correct
	frag_color = pow(frag_color, vec3(1.0f/ 2.2f)); 
	
	
	//final_frag_color = vec4(frag_color, 1.0f);
	final_frag_color = vec4(0.8f, 0.9f, 1.0f, 1.0f);

	//float t = texture(mat.roughness_map, frag_texture_coords).r;
	//final_frag_color = vec4(texture(mat.displacement_map, frag_uv).r, 0.0f, 0.0f, 1.0f);
	//final_frag_color = vec4(frag_disp, 0.0f, 0.0f, 1.0f);
}

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

vec3 GetNormalFromMap(vec3 normal, sampler2D normal_map, vec2 uv, vec3 frag_position)
{
	 vec3 tangent_normal = texture(normal_map, uv).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(frag_position);
    vec3 Q2  = dFdy(frag_position);
    vec2 st1 = dFdx(uv);
    vec2 st2 = dFdy(uv);

    vec3 N   = normalize(normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

	return normalize(TBN * tangent_normal);
}

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

