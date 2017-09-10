#include "Graphics/Shaders/VertexShader.h"

#include <d3dcompiler.h>

using Microsoft::WRL::ComPtr;

namespace Giganugs::Graphics {

	VertexShader::VertexShader(const std::wstring& filename, const std::string& entryPoint, const VertexBufferDefinition& definition, Microsoft::WRL::ComPtr<ID3D11Device> device)
	{
		ComPtr<ID3DBlob> shaderCode;
		D3DCompileFromFile(filename.c_str(), nullptr, nullptr, entryPoint.c_str(), "vs_4_0", 0, 0, &shaderCode, nullptr);
		device->CreateVertexShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), nullptr, &shader);

		inputLayout = definition.createLayout(device, shaderCode);
	}


	VertexShader::~VertexShader()
	{
	}

	void VertexShader::Set(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
	{
		context->VSSetShader(shader.Get(), nullptr, 0);
		context->IASetInputLayout(inputLayout.Get());
	}
}
