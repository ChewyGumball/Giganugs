#include "Resources/Catalogs/SpriteAtlasCatalog.h"

#include "Resources/Catalogs/TextureCatalog.h"


namespace Giganugs::Resources {

	SpriteAtlasCatalog::SpriteAtlasCatalog(const std::vector<std::string>& resourceLocations, TextureCatalog* textureCatalog)
		:ResourceCatalog<Sprites::SpriteAtlas>(resourceLocations), textureCatalog(textureCatalog)
	{
	}


	SpriteAtlasCatalog::~SpriteAtlasCatalog()
	{
	}

	Sprites::SpriteAtlas* Giganugs::Resources::SpriteAtlasCatalog::create(const std::string & filename, uint32_t ID) const
	{
		return new Sprites::SpriteAtlas(ID, filename, textureCatalog);
	}

	bool Giganugs::Resources::SpriteAtlasCatalog::reload(const std::string & filename, Sprites::SpriteAtlas& resource) const
	{
		return resource.reload(filename, textureCatalog);
	}
}
