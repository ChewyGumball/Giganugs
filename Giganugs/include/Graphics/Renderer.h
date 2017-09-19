#pragma once
#include <cstdint>
#include <d3d11.h>
#include <dxgi1_4.h>
#include <wrl.h>

#include <vector>

#include "Graphics/Shaders/SpriteShader.h"

#include "Sprites/SpriteAtlas.h"

namespace Giganugs::Graphics {
	class Window;
	class VertexBuffer;

	class Renderer
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> device;
		Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> backBuffer;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> defaultSampler;

		SpriteShader* spriteShader;

		Microsoft::WRL::ComPtr<ID3D11Buffer> cameraBuffer;

		D3D_FEATURE_LEVEL featureLevel;
		
	public:

		Renderer(const Window* const window);
		~Renderer();
		Microsoft::WRL::ComPtr<ID3D11Device> getDevice();

		void setTexture(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture);
		void setBatch(std::vector<Giganugs::Sprites::SpriteInstanceData>& parts);

		void Draw(uint32_t instanceCount);
		void Clear();
		void Swap();
	};
}
