#pragma once
#include <vector>

#include <wrl.h>

#include "Graphics/VertexBufferDefinition.h"

namespace Giganugs::Graphics {
	class VertexBuffer
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

	public:
		const VertexBufferDefinition definition;

		VertexBuffer(VertexBufferDefinition definition, std::vector<float> &data, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context, Microsoft::WRL::ComPtr<ID3D11Device> device);
		~VertexBuffer();

		void Set(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
	};
}
