#pragma once
#include <wrl.h>
#include <string>

#include <d3d11.h>

#include "Graphics/VertexBufferDefinition.h"

namespace Giganugs::Graphics {

	class VertexShader
	{
		Microsoft::WRL::ComPtr<ID3D11VertexShader> shader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

	public:
		VertexShader(const std::wstring& filename, const std::string& entryPoint, const VertexBufferDefinition& definition, Microsoft::WRL::ComPtr<ID3D11Device> device);
		~VertexShader();

		void Set(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
	};
}
