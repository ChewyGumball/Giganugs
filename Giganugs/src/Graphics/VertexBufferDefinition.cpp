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
		{ DXGI_FORMAT_R32G32B32A32_FLOAT , static_cast<uint32_t>(sizeof(float) * 4) },
	};
}

using Microsoft::WRL::ComPtr;

namespace Giganugs::Graphics {

	VertexBufferDefinition::VertexBufferDefinition(D3D11_PRIMITIVE_TOPOLOGY topology, std::vector<InputElement> elements) : topology(topology), elements(elements), bufferSize(0)
	{
		for (auto& element : elements) {
			bufferSize += sizes[element.Format];
		}
	}


	VertexBufferDefinition::~VertexBufferDefinition()
	{
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

	VertexBufferDefinition VertexBufferDefinition::operator+(const VertexBufferDefinition & other) const
	{
		std::vector<InputElement> combinedElements;

		for (auto& element : elements) {
			combinedElements.push_back(element);
		}
		for (auto& element : other.elements) {
			combinedElements.push_back(element);
		}

		return VertexBufferDefinition(topology, combinedElements);
	}

	InputElement::InputElement(VertexSemantic semantic, DXGI_FORMAT format)
		:InputElement(semantic, 0, D3D11_INPUT_PER_VERTEX_DATA, format)
	{ }

	InputElement::InputElement(VertexSemantic semantic, uint32_t index, DXGI_FORMAT format)
		: InputElement(semantic, index, D3D11_INPUT_PER_VERTEX_DATA, format)
	{ }

	InputElement::InputElement(VertexSemantic semantic, uint32_t index, D3D11_INPUT_CLASSIFICATION type, DXGI_FORMAT format)
		: InputElement(semantic, index, type, format, 0)
	{ }

	InputElement::InputElement(VertexSemantic semantic, uint32_t index, D3D11_INPUT_CLASSIFICATION type, DXGI_FORMAT format, uint32_t slot)
	{
		SemanticName = semantics[semantic];
		SemanticIndex = index;
		Format = format;
		InputSlot = slot;
		AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		InputSlotClass = type;
		InstanceDataStepRate = type == D3D11_INPUT_PER_INSTANCE_DATA ? 1 : 0;
	}
}
