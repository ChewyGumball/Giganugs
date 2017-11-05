#pragma once

#include <d3d11.h>
#include <wrl.h>

#include <vector>

#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexBufferDefinition.h"

#include "Sprites/SpriteAtlasPart.h"

#include "Graphics/Shaders/VertexShader.h"
#include "Graphics/Shaders/PixelShader.h"
#include "Sprites/SpriteBatch.h"

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
		const int MaxBatchSize;

		SpriteShader(Microsoft::WRL::ComPtr<ID3D11Device> device, int maxBatchSize);
		~SpriteShader();

		void setBatch(const Giganugs::Sprites::SpriteBatch& batch, int start, int count, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);

		void Set(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
	};
}
