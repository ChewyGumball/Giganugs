#include "Graphics/Shaders/PixelShader.h"

#include <d3dcompiler.h>

using Microsoft::WRL::ComPtr;

namespace Giganugs::Graphics {

	PixelShader::PixelShader(const std::wstring& filename, const std::string& entryPoint, ComPtr<ID3D11Device> device)
	{
		ComPtr<ID3DBlob> shaderCode;
		D3DCompileFromFile(filename.c_str(), nullptr, nullptr, entryPoint.c_str(), "ps_4_0", 0, 0, &shaderCode, nullptr);
		device->CreatePixelShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), nullptr, &shader);
	}


	PixelShader::~PixelShader()
	{
	}
	void PixelShader::Set(ComPtr<ID3D11DeviceContext> context)
	{
		context->PSSetShader(shader.Get(), nullptr, 0);
	}
	void PixelShader::SetTexture(int32_t slot, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
	{
		context->PSSetShaderResources(slot, 1, texture.GetAddressOf());
		context->PSSetSamplers(slot, 1, sampler.GetAddressOf());
	}
}
