#pragma once
#include <vector>
#include <unordered_map>
#include <string>

#include <wrl.h>
#include <d3d11.h>

#include "Graphics/Texture.h"
#include "Resources/Resource.h"
#include "Resources/ResourceCatalog.h"
#include "Sprites/SpriteAtlasPart.h"

namespace Giganugs::Sprites {
	class SpriteAtlas : public Resources::Resource<SpriteAtlas>
	{
		std::vector<SpriteAtlasPart> parts;
		std::unordered_map<std::string, int32_t> namesToIndices;
		Graphics::Texture* m_texture;


	public:
		SpriteAtlas(uint32_t ID, const std::string& filename, Resources::ResourceCatalog<Graphics::Texture>* textureCatalog);
		~SpriteAtlas();

		int32_t indexOf(const std::string& spriteName) const;

		SpriteAtlasPart part(uint32_t index) const;

		uint32_t partCount() const;

		Graphics::Texture* texture() const;

		bool reload(const std::string& filename, Resources::ResourceCatalog<Graphics::Texture>* textureCatalog);
	};
}
