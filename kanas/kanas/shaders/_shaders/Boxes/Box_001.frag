#version 450 core

struct AmbientLight
{
	vec3 Color;
};

struct DirectionalLight
{
	vec3 Color;
	vec3 Direction;
};

struct PointLight
{
	vec3 Color;
	vec3 Position;

	float Constant;
	float Linear;
	float Quadratic;
};

struct SpotLight
{
	vec3 Color;
	vec3 Position;
	vec3 Direction;

	float CosPhy;
};

struct Material
{
	sampler2D AmbientTextureFactor;
	sampler2D DiffuseTextureFactor;
	sampler2D SpecularTextureFactor;
	float Shininess;
};

uniform AmbientLight oAmbientLight;

#define MAX_NUM_DIRECTIONAL_LIGHT 10
#define MAX_NUM_POINT_LIGHT 10
#define MAX_NUM_SPOT_LIGHT 10
uniform int oDirectionalLightsNum;
uniform int oPointLightsNum;
uniform int oSpotLightsNum;
uniform DirectionalLight oDirectionalLights[MAX_NUM_DIRECTIONAL_LIGHT];
uniform PointLight oPointLights[MAX_NUM_POINT_LIGHT];
uniform SpotLight oSpotLights[MAX_NUM_SPOT_LIGHT];

uniform Material oMaterial;
uniform vec3 oCameraPosition;

in vec3 tFragmentPosition;
in vec3 tNormal;
in vec2 tTextureCoordinate;
//in vec3 tColor;

out vec4 tFragmentColor;

void main()
{
	vec3 Normal = normalize(tNormal);
	vec3 ViewDirection = normalize(tFragmentPosition - oCameraPosition);

	//~Ambient
	vec3 AmbientTextureFactor = texture(oMaterial.AmbientTextureFactor, tTextureCoordinate).rgb;
	vec3 AmbientFactor = AmbientTextureFactor * oAmbientLight.Color;
	//~Ambient

	//~Diffuse ~Specular
	vec3 DiffuseFactor = vec3(0.0f, 0.0f, 0.0f);
	vec3 SpecularFactor = vec3(0.0f, 0.0f, 0.0f);
	vec3 CameraDirection = normalize(oCameraPosition - tFragmentPosition);
		int DLNum = 0;
		if(oDirectionalLightsNum <= MAX_NUM_DIRECTIONAL_LIGHT)
		{
			DLNum = oDirectionalLightsNum;
		}else{
			DLNum = MAX_NUM_DIRECTIONAL_LIGHT;
		}

		for(int i = 0; i < DLNum; ++i)
		{
			vec3 DirectionalLightDirection = normalize(oDirectionalLights[i].Direction);
			DiffuseFactor += max(dot(DirectionalLightDirection, Normal), 0) * oDirectionalLights[i].Color;
			
			vec3 DirectionalLightReflectDirection = reflect(DirectionalLightDirection, Normal);
			SpecularFactor += pow(max(dot(CameraDirection, DirectionalLightReflectDirection), 0), oMaterial.Shininess)* oDirectionalLights[i].Color;
		}
		
		int PLNum = 0;
		if(oPointLightsNum <= MAX_NUM_POINT_LIGHT)
		{
			PLNum = oPointLightsNum;
		}else{
			PLNum = MAX_NUM_POINT_LIGHT;
		}

		for(int i = 0; i < PLNum; ++i)
		{
			float PointLightDistance = length(oPointLights[i].Position - tFragmentPosition);
			float PointLightAttenuation 
				= 1.0f/ (oPointLights[i].Constant + oPointLights[i].Linear * PointLightDistance + oPointLights[i].Quadratic * (PointLightDistance * PointLightDistance));
			vec3 PointLightDirection = normalize(tFragmentPosition - oPointLights[i].Position);
			DiffuseFactor += PointLightAttenuation * max(dot(PointLightDirection, Normal), 0) * oPointLights[i].Color;

			vec3 PointLightReflectDirection = reflect(PointLightDirection, Normal);
			SpecularFactor += PointLightAttenuation * pow(max(dot(CameraDirection, PointLightReflectDirection), 0), oMaterial.Shininess) * oPointLights[i].Color;
		}
		
		int SLNum = 0;
		if(oSpotLightsNum <= MAX_NUM_SPOT_LIGHT)
		{
			SLNum = oSpotLightsNum;
		}else{
			SLNum = MAX_NUM_SPOT_LIGHT;
		}

		for(int i = 0; i < SLNum; ++i)
		{
			vec3 SpotLightDirection = normalize(oSpotLights[i].Direction);
			vec3 SpotLightReflectDirection = reflect(SpotLightDirection, Normal);
			float CosTheta = dot(normalize(tFragmentPosition - oSpotLights[i].Position), -1 * SpotLightDirection);

			if(oSpotLights[i].CosPhy < CosTheta)
			{
				DiffuseFactor +=  max(dot(SpotLightDirection, Normal), 0) * oSpotLights[i].Color;
				SpecularFactor += pow(max(dot(CameraDirection, SpotLightReflectDirection), 0), oMaterial.Shininess)* oSpotLights[i].Color;
			}
		}
		
	vec3 DiffuseTextureFactor = texture(oMaterial.DiffuseTextureFactor, tTextureCoordinate).rgb;
	DiffuseFactor *= DiffuseTextureFactor;

	vec3 SpecularTextureFactor = texture(oMaterial.SpecularTextureFactor, tTextureCoordinate).rgb;
	SpecularFactor *= SpecularTextureFactor;

	//tFragmentColor = vec4((AmbientFactor + DiffuseFactor), 1.0f);
	tFragmentColor = vec4((AmbientFactor + DiffuseFactor + SpecularFactor), 1.0f);
	//tFragmentColor = vec4((AmbientFactor + DiffuseFactor + SpecularFactor) * tColor, 1.0f);
	//tFragmentColor = vec4(0.8, 0.1, 0.9, 1.0);
}
