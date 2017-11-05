#pragma once
#include "Resources/ResourceCatalog.h"

#include "Sprites/SpriteAnimation.h"

namespace Giganugs::Resources {
	class SpriteAtlasCatalog;

	class SpriteAnimationCatalog : public ResourceCatalog<Sprites::SpriteAnimation>
	{
	private:
		SpriteAtlasCatalog* spriteAtlasCatalog;

	public:
		SpriteAnimationCatalog(const std::vector<std::string>& resourceLocations, SpriteAtlasCatalog* spriteAtlasCatalog);
		~SpriteAnimationCatalog();

	protected:
		// Inherited via ResourceCatalog
		virtual Sprites::SpriteAnimation * create(const std::string & filename, uint32_t ID) const override;
		virtual bool reload(const std::string & filename, Sprites::SpriteAnimation & resource) const override;
	};
}
