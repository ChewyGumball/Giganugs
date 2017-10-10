
Texture2D spriteTexture : register(t0);
sampler spriteSampler : register(s0);

cbuffer Camera : register(b0) {
	float4x4 viewProjection;
};

struct Vertex {
	float2 basePosition: POSITION0;
	float4 position: POSITION1;
	float4 spriteDetails: TEXCOORD;
};

struct Pixel {
	float4 position: SV_POSITION;
	float2 textureCoordinates: TEXCOORD;
};

Pixel vertexShader(Vertex vertex)
{
	Pixel output;

	float4 position = float4(vertex.position.xy + (vertex.basePosition * vertex.position.zw) + vertex.basePosition, 0, 1);

	output.position = mul(viewProjection, position);
	output.textureCoordinates = float2(vertex.spriteDetails.x + vertex.spriteDetails.z * vertex.basePosition.x, vertex.spriteDetails.y + vertex.spriteDetails.w * (1 - vertex.basePosition.y));

	return output;
}

float4 pixelShader(Pixel pixel) : SV_TARGET {
	float4 colour = spriteTexture.Sample(spriteSampler, pixel.textureCoordinates);
	if (colour.a < 0.01) discard;

	return colour;
}