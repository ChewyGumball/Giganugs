
Texture2D spriteTexture : register(t0);
sampler spriteSampler : register(s0);

struct Vertex {
	float4 position: POSITION;
	float2 textureCoordinates: TEXCOORD;
};

struct Pixel {
	float4 position: SV_POSITION;
	float2 textureCoordinates: TEXCOORD;
};

Pixel vertexShader(Vertex vertex)
{
	Pixel output;

	output.position = vertex.position;
	output.textureCoordinates = vertex.textureCoordinates;

	return output;
}

float4 pixelShader(Pixel pixel) : SV_TARGET {
	return spriteTexture.Sample(spriteSampler, pixel.textureCoordinates);
}