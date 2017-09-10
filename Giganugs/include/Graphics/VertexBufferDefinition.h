#pragma once
#include <vector>

#include <wrl.h>
#include <d3d11.h>

namespace Giganugs::Graphics {

	enum VertexSemantic {
		POSITION,
		TEXCOORD
	};

	class VertexBufferDefinition
	{
	private:
		std::vector<D3D11_INPUT_ELEMENT_DESC> elements;
		uint32_t bufferSize;

	public:
		VertexBufferDefinition(std::vector<std::pair<VertexSemantic, DXGI_FORMAT>> elements);
		~VertexBufferDefinition();

		void addElement(VertexSemantic semantic, DXGI_FORMAT format);

		uint32_t size() const;

		Microsoft::WRL::ComPtr<ID3D11InputLayout> createLayout(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3DBlob> shaderCode) const;
	};
}
