#include "Resources/Catalogs/SpriteAnimationCatalog.h"

namespace Giganugs::Resources {

	SpriteAnimationCatalog::SpriteAnimationCatalog(const std::vector<std::string>& resourceLocations, SpriteAtlasCatalog* spriteAtlasCatalog)
		:ResourceCatalog(resourceLocations), spriteAtlasCatalog(spriteAtlasCatalog)
	{
	}


	SpriteAnimationCatalog::~SpriteAnimationCatalog()
	{
	}
	Sprites::SpriteAnimation * SpriteAnimationCatalog::create(const std::string & filename, uint32_t ID)
	{
		return new Sprites::SpriteAnimation(ID, filename, spriteAtlasCatalog);
	}
	bool SpriteAnimationCatalog::reload(const std::string & filename, Sprites::SpriteAnimation & resource)
	{
		return resource.reload(filename, spriteAtlasCatalog);
	}
}
