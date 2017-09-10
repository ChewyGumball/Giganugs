#include "Graphics/VertexBuffer.h"
using Microsoft::WRL::ComPtr;
namespace Giganugs::Graphics {
	
	VertexBuffer::VertexBuffer(VertexBufferDefinition definition, std::vector<float>& data, ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11Device> device)
		: definition(definition)
	{
		D3D11_BUFFER_DESC vertexBufferDescription;
		ZeroMemory(&vertexBufferDescription, sizeof(D3D11_BUFFER_DESC));

		vertexBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDescription.ByteWidth = sizeof(float) * data.size();
		vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		device->CreateBuffer(&vertexBufferDescription, nullptr, &buffer);

		D3D11_MAPPED_SUBRESOURCE mappedVertexBuffer;
		context->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedVertexBuffer);
		
		std::memcpy(mappedVertexBuffer.pData, data.data(), vertexBufferDescription.ByteWidth);

		context->Unmap(buffer.Get(), 0);
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	void VertexBuffer::Set(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
	{
		uint32_t stride = definition.size();
		uint32_t offset = 0;
		context->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, &offset);
	}
}
