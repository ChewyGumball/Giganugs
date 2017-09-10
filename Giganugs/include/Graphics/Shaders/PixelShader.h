#pragma once
#include <string>
#include <wrl.h>

#include <d3d11.h>

namespace Giganugs::Graphics {
	class PixelShader
	{
		Microsoft::WRL::ComPtr<ID3D11PixelShader> shader;
	public:
		PixelShader(const std::wstring& filename, const std::string& entryPoint, Microsoft::WRL::ComPtr<ID3D11Device> device);
		~PixelShader();

		void Set(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
	};
}
