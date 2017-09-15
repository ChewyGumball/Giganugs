#pragma once

#include <d3d11.h>
#include <wrl.h>

#include <vector>

#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexBufferDefinition.h"

#include "Sprites/SpriteAtlasPart.h"

#include "Graphics/Shaders/VertexShader.h"
#include "Graphics/Shaders/PixelShader.h"

namespace Giganugs::Graphics {
	class VertexShader;
	class PixelShader;

	class SpriteShader
	{
		VertexBuffer vertexData;
		VertexBuffer batchData;

		VertexBufferDefinition bufferDefinition;
		VertexShader vertexShader;
		PixelShader pixelShader;

	public:
		SpriteShader(Microsoft::WRL::ComPtr<ID3D11Device> device);
		~SpriteShader();

		void setBatch(std::vector<Giganugs::Sprites::SpriteInstanceData> parts, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);

		void Set(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
	};
}
