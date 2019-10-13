#version 330

layout(location = 0) in vec3 inPosition;

out vertexData
{
	vec2 texcoord;
} outData;

void main()
{
	vec4 position = vec4(inPosition,1.0);
	outData.texcoord = position.xy;

	gl_Position = position;
}
