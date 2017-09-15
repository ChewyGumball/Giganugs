#include "Graphics/VertexBuffer.h"

#include <d3d11.h>

using Microsoft::WRL::ComPtr;
namespace Giganugs::Graphics {
	VertexBuffer::VertexBuffer(VertexBufferDefinition definition, uint32_t elementCount, Microsoft::WRL::ComPtr<ID3D11Device> device)
		:definition(definition)
	{
		D3D11_BUFFER_DESC vertexBufferDescription = {};
		vertexBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDescription.ByteWidth = elementCount * definition.size();
		vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		device->CreateBuffer(&vertexBufferDescription, nullptr, &buffer);
	}

	VertexBuffer::VertexBuffer(VertexBufferDefinition definition, std::vector<float>& data, ComPtr<ID3D11Device> device)
		: definition(definition)
	{
		D3D11_BUFFER_DESC vertexBufferDescription = {};
		vertexBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDescription.ByteWidth = static_cast<uint32_t>(sizeof(float) * data.size());
		vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = data.data();

		device->CreateBuffer(&vertexBufferDescription, &vertexData, &buffer);
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	D3D11_MAPPED_SUBRESOURCE VertexBuffer::Map(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
	{
		D3D11_MAPPED_SUBRESOURCE mapped;
		if (FAILED(context->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped))) {
			MessageBox(nullptr, L"Failed to map vertex buffer", L"FAIL", 0);
		}

		return mapped;
	}

	void VertexBuffer::Unmap(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
	{
		context->Unmap(buffer.Get(), 0);
	}

	void VertexBuffer::Set(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context, uint32_t slot)
	{
		uint32_t stride = definition.size();
		uint32_t offset = 0;
		context->IASetVertexBuffers(slot, 1, buffer.GetAddressOf(), &stride, &offset);
	}
}
