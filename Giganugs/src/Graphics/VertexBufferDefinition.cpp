#include "Graphics/VertexBufferDefinition.h"

#include <unordered_map>

namespace {
	std::unordered_map<Giganugs::Graphics::VertexSemantic, const char*> semantics = {
		{ Giganugs::Graphics::VertexSemantic::POSITION, "POSITION" },
		{ Giganugs::Graphics::VertexSemantic::TEXCOORD, "TEXCOORD" }
	};

	std::unordered_map<DXGI_FORMAT, uint32_t> sizes = {
		{ DXGI_FORMAT_R32G32B32_FLOAT , static_cast<uint32_t>(sizeof(float) * 3) },
		{ DXGI_FORMAT_R32G32_FLOAT , static_cast<uint32_t>(sizeof(float) * 2) },
	};
}

using Microsoft::WRL::ComPtr;

namespace Giganugs::Graphics {

	VertexBufferDefinition::VertexBufferDefinition(D3D11_PRIMITIVE_TOPOLOGY topology, std::vector<std::pair<VertexSemantic, DXGI_FORMAT>> elements) : topology(topology), bufferSize(0)
	{
		for (auto& element : elements) {
			addElement(element.first, element.second);
		}
	}


	VertexBufferDefinition::~VertexBufferDefinition()
	{
	}

	void VertexBufferDefinition::addElement(VertexSemantic semantic, DXGI_FORMAT format)
	{
		elements.push_back({ semantics[semantic], 0, format, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		bufferSize += sizes[format];
	}

	uint32_t VertexBufferDefinition::size() const
	{
		return bufferSize;
	}

	D3D11_PRIMITIVE_TOPOLOGY VertexBufferDefinition::primitiveTopology() const
	{
		return topology;
	}

	ComPtr<ID3D11InputLayout> VertexBufferDefinition::createLayout(ComPtr<ID3D11Device> device, ComPtr<ID3DBlob> shaderCode) const
	{
		ComPtr<ID3D11InputLayout> layout;
		device->CreateInputLayout(elements.data(), static_cast<uint32_t>(elements.size()), shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), &layout);
		return layout;
	}
}
