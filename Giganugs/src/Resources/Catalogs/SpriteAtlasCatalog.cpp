#include "Resources/Catalogs/SpriteAtlasCatalog.h"

#include "Resources/Catalogs/TextureCatalog.h"


namespace Giganugs::Resources {

	SpriteAtlasCatalog::SpriteAtlasCatalog(std::vector<std::string> resourceLocations, TextureCatalog* textureCatalog)
		:ResourceCatalog<Sprites::SpriteAtlas>(resourceLocations), textureCatalog(textureCatalog)
	{
	}


	SpriteAtlasCatalog::~SpriteAtlasCatalog()
	{
	}

	Sprites::SpriteAtlas* Giganugs::Resources::SpriteAtlasCatalog::create(const std::string & filename, uint32_t ID)
	{
		return new Sprites::SpriteAtlas(ID, filename, textureCatalog);
	}

	void Giganugs::Resources::SpriteAtlasCatalog::reload(const std::string & filename, Sprites::SpriteAtlas& resource)
	{
	}
}
