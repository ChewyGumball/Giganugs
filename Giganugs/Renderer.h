#pragma once
#include <cstdint>
#include <d3d11.h>
#include <dxgi1_4.h>
#include <wrl.h>

namespace Giganugs::Graphics {
	class Window;

	class Renderer
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> device;
		Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> backBuffer;

		D3D_FEATURE_LEVEL featureLevel;
		
	public:
		Renderer(const Window* const window);
		~Renderer();

		void Clear();
		void Swap();
	};
}
