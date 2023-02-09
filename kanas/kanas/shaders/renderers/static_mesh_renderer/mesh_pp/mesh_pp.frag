#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_shading_language_include : require
#pragma STDGL invariant(all)
#pragma optimize(on)
#pragma debug(on)
#include "/common.glsl" //! #include "../../../templates/common.glsl"
#include "/common.frag.glsl" //! #include "../../../templates/common.frag.glsl"

in FragData
{
	vec3 position;
	vec2 uv;
	vec3 normal;
	float disp;
} inData;

layout(location = 0) out vec4 final_frag_color;

void main()
{

	vec3 N = GetNormalFromMap(inData.normal, mat.normal_map, inData.uv, inData.position);

	vec3 albedo = pow(texture(mat.albedo_map, inData.uv).rgb, vec3(2.2));
	float metalness = texture(mat.metalness_map, inData.uv).r;
	float roughness = texture(mat.roughness_map, inData.uv).r;
	float ambient_occlusion = texture(mat.ambient_occlusion_map, inData.uv).r;

	vec3 V = normalize(camera_position - inData.position);
	
	vec3 F0 = vec3(0.04f); // F0 (1-metalness) + albedo*metalness 
	F0 = mix(F0, albedo, metalness); // base reflectivity of the surface

	vec3 Lo = vec3(0.0f);

	for(int i = 0; i < en_lights.point_lights_num; ++i)
	{
		point_light light = en_lights.point_lights[i];

		float light_distance = length(light.position -inData.position);
		float attenuation = 1.0f / (light.constant + light.linear * light_distance + light.quadratic * pow(light_distance, 2)); //float attenuation = 1.0 / (light_distance * light_distance);
		
		vec3 radiance = light.color * attenuation;

		vec3 L = normalize(light.position - inData.position);
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