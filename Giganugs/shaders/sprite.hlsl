struct Vertex {
	float4 position: POSITION;
	float2 textureCoordinates: TEXCOORD;
};

struct Pixel {
	float4 position: SV_POSITION;
	float4 textureCoordinates: COLOR;
};

Pixel vertexShader(Vertex vertex)
{
	Pixel output;
	output.position = vertex.position;
	output.textureCoordinates = float4(vertex.textureCoordinates, 1, 0);

	return output;
}

float4 pixelShader(Pixel pixel) : SV_TARGET {
	return pixel.textureCoordinates;
}