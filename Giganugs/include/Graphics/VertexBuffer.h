#pragma once
#include <vector>
#include <wrl.h>

#include <d3d11.h>

#include "Graphics/VertexBufferDefinition.h"

namespace Giganugs::Graphics {

	class VertexBuffer
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

	public:
		const VertexBufferDefinition definition;

		VertexBuffer(VertexBufferDefinition definition, uint32_t elementCount, Microsoft::WRL::ComPtr<ID3D11Device> device);
		VertexBuffer(VertexBufferDefinition definition, std::vector<float> &data, Microsoft::WRL::ComPtr<ID3D11Device> device);
		~VertexBuffer();

		D3D11_MAPPED_SUBRESOURCE Map(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
		void Unmap(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);

		void Set(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context, uint32_t slot);
	};
}
