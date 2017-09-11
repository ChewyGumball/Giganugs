#pragma once
#include <vector>
#include <unordered_map>
#include <string>

#include <wrl.h>
#include <d3d11.h>

#include "Sprites/SpriteAtlasPart.h"

namespace Giganugs::Sprites {
	class SpriteAtlas
	{
		int ID;
		std::vector<SpriteAtlasPart> parts;
		std::unordered_map<std::string, int32_t> namesToIndices;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureView;


	public:
		SpriteAtlas(int ID, std::string_view filename, Microsoft::WRL::ComPtr<ID3D11Device> device);
		~SpriteAtlas();

		int32_t indexOf(const std::string& spriteName) const;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture() const;
	};
}
