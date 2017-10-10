#include "Graphics/Shaders/SpriteShader.h"


#include "Graphics/VertexBufferDefinition.h"

using Microsoft::WRL::ComPtr;

namespace {
	std::vector<float> vertexes = {
		0, 0,
		0, 1, 
		1, 0, 
		1, 1 
	};
}

namespace Giganugs::Graphics {

	SpriteShader::SpriteShader(ComPtr<ID3D11Device> device) : 
		vertexData(VertexBufferDefinition(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, {
			{ Giganugs::Graphics::VertexSemantic::POSITION, 0, DXGI_FORMAT_R32G32_FLOAT }
		}), vertexes, device),
		batchData(VertexBufferDefinition(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, {
			{ Giganugs::Graphics::VertexSemantic::POSITION, 1, D3D11_INPUT_PER_INSTANCE_DATA, DXGI_FORMAT_R32G32B32A32_FLOAT, 1 },
			{ Giganugs::Graphics::VertexSemantic::TEXCOORD, 0, D3D11_INPUT_PER_INSTANCE_DATA, DXGI_FORMAT_R32G32B32A32_FLOAT, 1 }
		}), 1000, device),
		bufferDefinition(vertexData.definition + batchData.definition),
		vertexShader(L"resources/shaders/sprite.hlsl", "vertexShader", bufferDefinition, device), 
		pixelShader(L"resources/shaders/sprite.hlsl", "pixelShader", device)
	{
	}

	SpriteShader::~SpriteShader()
	{
	}

	void SpriteShader::setBatch(const Giganugs::Sprites::SpriteBatch& batch, ComPtr<ID3D11DeviceContext> context)
	{
		size_t s = sizeof(Giganugs::Sprites::SpriteInstanceData);
		auto d = batchData.Map(context);
		std::memcpy(d.pData, batch.instances.data(), batch.instances.size() * s);
		batchData.Unmap(context);
	}

	void SpriteShader::Set(ComPtr<ID3D11DeviceContext> context)
	{
		vertexShader.Set(context);
		pixelShader.Set(context);
		vertexData.Set(context, 0);
		batchData.Set(context, 1);
		context->IASetPrimitiveTopology(bufferDefinition.primitiveTopology());
	}
}
