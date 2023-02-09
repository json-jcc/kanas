#version 460 core
#extension GL_ARB_shading_language_include : require

uniform mat4 TransformMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

layout(location = 0) in vec3 LocalPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;


void main()
{
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(LocalPosition, 1.0);
	
	TexCoord = aTexCoord;
	FragPos = vec3(ModelMatrix * vec4(LocalPosition, 1.0));
	Normal = mat3(transpose(inverse(ModelMatrix))) * aNormal;
}

subroutine vec4 LightFunc(vec3);

subroutine (LightFunc) 
vec4 ambient(vec3 n)
{
	return vec4(1,1,1,1);
}

subroutine (LightFunc) 
vec4 diffuse(vec3 n)
{
	return vec4(1,1,1,1) * max(dot(normalize(n), vec3(1,1,1)), 0.0);
}

subroutine uniform LightFunc materialShader;
