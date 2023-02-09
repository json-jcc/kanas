#version 450 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TextureCoordinate;

out vec3 tFragmentPosition;
out vec3 tNormal;
out vec2 tTextureCoordinate;

uniform mat4 TransformMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform vec3 Offsets[10];

void main()
{
	vec3 OffestPosition = Position + Offsets[gl_InstanceID];

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(OffestPosition, 1.0f);
	
	tFragmentPosition = vec3(ModelMatrix * vec4(OffestPosition, 1.0f));
	tNormal = mat3(transpose(inverse(ModelMatrix))) * Normal;
	tTextureCoordinate = TextureCoordinate;
	//tColor = SpecialColor;
	//gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(Position, 1.0f);
	
	//tFragmentPosition = vec3(ModelMatrix * vec4(Position, 1.0f));
	//tNormal = mat3(transpose(inverse(ModelMatrix))) * Normal;
	//tTextureCoordinate = TextureCoordinate;
}
