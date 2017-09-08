#include "Graphics/Renderer.h"
#include "Graphics/Window.h"

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <d3dcompiler.h>


using Microsoft::WRL::ComPtr;

namespace Giganugs::Graphics {
	Renderer::Renderer(const Window* const window)
	{
		//-- Create the swap chain --//
		DXGI_SWAP_CHAIN_DESC swapChainDescription;
		ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

		swapChainDescription.BufferCount = 1; 
		swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDescription.OutputWindow = window->handle();
		swapChainDescription.SampleDesc.Count = 4;
		swapChainDescription.Windowed = TRUE;

		uint32_t flags = 0;

#ifdef _DEBUG
		flags = D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, nullptr, 0, D3D11_SDK_VERSION, &swapChainDescription, &swapChain, &device, &featureLevel, &context);

		{
			ComPtr<ID3D11Texture2D> buffer;
			swapChain->GetBuffer(0, IID_PPV_ARGS(&buffer));
			device->CreateRenderTargetView(buffer.Get(), nullptr, &backBuffer);
		}

		context->OMSetRenderTargets(1, backBuffer.GetAddressOf(), nullptr);

		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = static_cast<float>(window->Width());
		viewport.Height = static_cast<float>(window->Height());
		context->RSSetViewports(1, &viewport);

		ComPtr<ID3DBlob> vertexCode;
		ComPtr<ID3DBlob> pixelCode;
		D3DCompileFromFile(L"shaders/sprite.hlsl", nullptr, nullptr, "vertexShader", "vs_4_0", 0, 0, &vertexCode, nullptr);
		D3DCompileFromFile(L"shaders/sprite.hlsl", nullptr, nullptr, "pixelShader", "ps_4_0", 0, 0, &pixelCode, nullptr);

		device->CreateVertexShader(vertexCode->GetBufferPointer(), vertexCode->GetBufferSize(), nullptr, &vertexShader);
		device->CreatePixelShader(pixelCode->GetBufferPointer(), pixelCode->GetBufferSize(), nullptr, &pixelShader);

		context->VSSetShader(vertexShader.Get(), nullptr, 0);
		context->PSSetShader(pixelShader.Get(), nullptr, 0);

		D3D11_BUFFER_DESC vertexBufferDescription;
		ZeroMemory(&vertexBufferDescription, sizeof(D3D11_BUFFER_DESC));

		vertexBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDescription.ByteWidth = sizeof(float) * 5 * 4; // [x y z] [s t] * 4
		vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		
		device->CreateBuffer(&vertexBufferDescription, nullptr, &vertexBuffer);

		D3D11_MAPPED_SUBRESOURCE mappedVertexBuffer;
		context->Map(vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedVertexBuffer);

		float vertexData[] = {
			0, 0, 0,    0, 0,
			0, 1, 0,    0, 1,
			1, 0, 0,    1, 0,
			1, 1, 0,    1, 1
		};

		std::memcpy(mappedVertexBuffer.pData, vertexData, vertexBufferDescription.ByteWidth);

		context->Unmap(vertexBuffer.Get(), 0);

		D3D11_INPUT_ELEMENT_DESC vertexLayout[] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		device->CreateInputLayout(vertexLayout, 2, vertexCode->GetBufferPointer(), vertexCode->GetBufferSize(), &vertexBufferLayout);
		context->IASetInputLayout(vertexBufferLayout.Get());
	}


	Renderer::~Renderer()
	{
	}

	void Renderer::Draw()
	{
		uint32_t stride = sizeof(float) * 5;
		uint32_t offset = 0;
		context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		context->Draw(4, 0);
	}

	void Renderer::Clear()
	{
		float clearColour[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
		context->ClearRenderTargetView(backBuffer.Get(), clearColour);
	}
	void Renderer::Swap()
	{
		swapChain->Present(0, 0);
	}
}
