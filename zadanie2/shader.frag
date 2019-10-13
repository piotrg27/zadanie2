#version 330 core

out vec4 outputColor;
uniform sampler2D textureSampler;

in vertexData
{
	vec2 texcoord;
} inData;

void main()
{	
	vec4 textureColor = texture(textureSampler, inData.texcoord);
	outputColor = vec4(inData.texcoord, 1.0, 1.0);
}
