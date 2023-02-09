#version 450 core

layout(location = 0) in vec3 Position;

out vec3 tFragmentPosition;

uniform mat4 TransformMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform vec3 PatchPositions[4];

out vec3 position_out;

void main()
{
	vec3 OffsetPosition = Position + PatchPositions[gl_InstanceID];

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(OffsetPosition, 1.0f);

	if(gl_InstanceID == 0)
	{
		position_out = Position + vec3(0.0f, 0.001f, 0.0f);
	}
	else
	{
		position_out = Position;
	}

	tFragmentPosition = vec3(ModelMatrix * vec4(OffsetPosition, 1.0f));
}