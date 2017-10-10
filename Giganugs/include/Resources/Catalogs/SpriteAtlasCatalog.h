#pragma once

#include "Sprites/SpriteAtlas.h"
#include "Resources/ResourceCatalog.h"

namespace Giganugs::Resources {
	class TextureCatalog;

	class SpriteAtlasCatalog : public ResourceCatalog<Sprites::SpriteAtlas>
	{
	private:
		TextureCatalog* textureCatalog;

	public:
		SpriteAtlasCatalog(std::vector<std::string> resourceLocations, TextureCatalog* textureCatalog);
		virtual ~SpriteAtlasCatalog();

		// Inherited via ResourceCatalog
		virtual Sprites::SpriteAtlas* create(const std::string & filename, uint32_t ID) override;
		virtual void reload(const std::string & filename, Sprites::SpriteAtlas& resource) override;
	};
}