#pragma once
#include <vector>

#include "Resources/Resource.h"

namespace Giganugs::Resources {
	class SpriteAtlasCatalog;
}
namespace Giganugs::Sprites {
	class SpriteAtlas;

	class SpriteAnimation : public Resources::Resource<SpriteAnimation>
	{
		float m_secondsPerFrame;

	public:
		std::vector<uint32_t> frames;

		SpriteAnimation(uint32_t ID, std::string_view filename, Resources::SpriteAtlasCatalog* atlasCatalog);
		~SpriteAnimation();

		float secondsPerFrame() const;

		bool reload(const std::string_view & filename, Resources::SpriteAtlasCatalog* atlasCatalog);
	};
}
