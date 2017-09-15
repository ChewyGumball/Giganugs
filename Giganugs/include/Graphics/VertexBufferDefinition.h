#pragma once
#include <vector>
#include <wrl.h>

#include <d3d11.h>

namespace Giganugs::Graphics {

	enum VertexSemantic {
		POSITION,
		TEXCOORD,
	};

	struct InputElement : public D3D11_INPUT_ELEMENT_DESC {
		InputElement(VertexSemantic semantic, DXGI_FORMAT format);
		InputElement(VertexSemantic semantic, uint32_t index, DXGI_FORMAT format);
		InputElement(VertexSemantic semantic, uint32_t index, D3D11_INPUT_CLASSIFICATION type, DXGI_FORMAT format);
		InputElement(VertexSemantic semantic, uint32_t index, D3D11_INPUT_CLASSIFICATION type, DXGI_FORMAT format, uint32_t slot);
	};

	class VertexBufferDefinition
	{
	private:
		
		D3D11_PRIMITIVE_TOPOLOGY topology;
		std::vector<InputElement> elements;
		uint32_t bufferSize;

	public:
		VertexBufferDefinition(D3D11_PRIMITIVE_TOPOLOGY topology, std::vector<InputElement> elements);
		~VertexBufferDefinition();
		
		uint32_t size() const;
		D3D11_PRIMITIVE_TOPOLOGY primitiveTopology() const;

		Microsoft::WRL::ComPtr<ID3D11InputLayout> createLayout(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3DBlob> shaderCode) const;

		VertexBufferDefinition operator+(const VertexBufferDefinition& other) const;
	};
}
