#include "Graphics/Renderer.h"
#include "Graphics/Window.h"
#include "Graphics/VertexBufferDefinition.h"
#include "Graphics/VertexBuffer.h"


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
		D3DCompileFromFile(L"resources/shaders/sprite.hlsl", nullptr, nullptr, "vertexShader", "vs_4_0", 0, 0, &vertexCode, nullptr);
		D3DCompileFromFile(L"resources/shaders/sprite.hlsl", nullptr, nullptr, "pixelShader", "ps_4_0", 0, 0, &pixelCode, nullptr);

		device->CreateVertexShader(vertexCode->GetBufferPointer(), vertexCode->GetBufferSize(), nullptr, &vertexShader);
		device->CreatePixelShader(pixelCode->GetBufferPointer(), pixelCode->GetBufferSize(), nullptr, &pixelShader);

		context->VSSetShader(vertexShader.Get(), nullptr, 0);
		context->PSSetShader(pixelShader.Get(), nullptr, 0);

		VertexBufferDefinition bufferDefinition({
			{ VertexSemantic::POSITION, DXGI_FORMAT_R32G32B32_FLOAT },
			{ VertexSemantic::TEXCOORD, DXGI_FORMAT_R32G32_FLOAT }
		});

		std::vector<float> vertexData = {
			-0.5, -0.5, 0,    0, 0,
			-0.5,  0.5, 0,    0, 1,
			 0.5, -0.5, 0,    1, 0,
			 0.5,  0.5, 0,    1, 1
		};

		vertexBuffer = new VertexBuffer(bufferDefinition, vertexData, context, device);
		vertexBufferLayout = vertexBuffer->definition.createLayout(device, vertexCode);
		context->IASetInputLayout(vertexBufferLayout.Get());
	}


	Renderer::~Renderer()
	{
		delete vertexBuffer;
	}

	Microsoft::WRL::ComPtr<ID3D11Device> Renderer::getDevice()
	{
		return device;
	}

	void Renderer::Draw()
	{
		vertexBuffer->Set(context);
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
