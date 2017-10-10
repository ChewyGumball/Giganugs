#include "Graphics/Renderer.h"
#include "Graphics/Window.h"
#include "Graphics/VertexBufferDefinition.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/Camera.h"


//#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <d3dcompiler.h>


#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"

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
		
		spriteShader = new SpriteShader(device);
		spriteShader->Set(context);
		
		D3D11_SAMPLER_DESC samplerDescription = {};
		samplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescription.Filter = D3D11_FILTER_ANISOTROPIC;
		samplerDescription.MinLOD = 0;
		samplerDescription.MaxLOD = D3D11_FLOAT32_MAX;

		device->CreateSamplerState(&samplerDescription, &defaultSampler); 
		
		D3D11_BUFFER_DESC cameraBufferDescription = {};

		cameraBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
		cameraBufferDescription.ByteWidth = sizeof(glm::mat4x4);
		cameraBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cameraBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cameraBufferDescription.MiscFlags = 0;

		glm::mat4x4 projection = glm::ortho(0.f, 10.f, 0.f, 10.f, 0.f, 10.f);
		D3D11_SUBRESOURCE_DATA cameraData = {};
		cameraData.pSysMem = &projection;

		if (FAILED(device->CreateBuffer(&cameraBufferDescription, &cameraData, &cameraBuffer))) {
			MessageBox(window->handle(), L"Failed to make camera buffer", L"FAIL", 0);
		}
		context->VSSetConstantBuffers(0, 1, cameraBuffer.GetAddressOf());
	}


	Renderer::~Renderer()
	{
		delete spriteShader;
	}

	Microsoft::WRL::ComPtr<ID3D11Device> Renderer::getDevice()
	{
		return device;
	}

	void Renderer::setTexture(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture)
	{
		context->PSSetShaderResources(0, 1, texture.GetAddressOf());
		context->PSSetSamplers(0, 1, defaultSampler.GetAddressOf());
	}

	void Renderer::setBatch(const Giganugs::Sprites::SpriteBatch& batch)
	{
		setTexture(batch.atlas->texture()->view());
		spriteShader->setBatch(batch, context);
	}

	void Renderer::setCamera(const Camera & camera)
	{
		D3D11_MAPPED_SUBRESOURCE mapped;
		if (FAILED(context->Map(cameraBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped))) {
			MessageBox(nullptr, L"Failed to map camera buffer", L"FAIL", 0);
		}

		glm::mat4 viewProjection = camera.viewProjection();
		std::memcpy(mapped.pData, &viewProjection, sizeof(glm::mat4));

		context->Unmap(cameraBuffer.Get(), 0);
	}

	void Renderer::Draw(uint32_t instanceCount)
	{
		context->DrawInstanced(4, instanceCount, 0, 0);
	}

	void Renderer::Draw(const Sprites::SpriteBatch & batch)
	{
		setBatch(batch);
		Draw(batch.instances.size());
	}

	void Renderer::Clear()
	{
		float clearColour[4] = { 0.15f, 0.15f, 0.15f, 1.0f };
		context->ClearRenderTargetView(backBuffer.Get(), clearColour);
	}
	void Renderer::Swap()
	{
		swapChain->Present(0, 0);
	}
}
