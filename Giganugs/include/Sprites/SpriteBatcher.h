#pragma once
#include <unordered_map>

#include "Resources/Catalogs/SpriteAtlasCatalog.h"
#include "Resources/ResourceTag.h"

namespace Giganugs::Sprites {
	class SpriteAtlas;
	class SpriteBatch;
	struct SpriteInstanceData;

	class SpriteBatcher
	{
	private:
		std::unordered_map<Giganugs::Resources::ResourceTag<SpriteAtlas>, SpriteBatch> batches;

		int maxBatchSize; 
		Giganugs::Resources::SpriteAtlasCatalog atlasCatalog;

	public:
		SpriteBatcher(int maxBatchSize, Giganugs::Resources::SpriteAtlasCatalog atlasCatalog);
		~SpriteBatcher();

		void add(Giganugs::Resources::ResourceTag<SpriteAtlas> atlasID, SpriteInstanceData instanceData);
		void add(Giganugs::Resources::ResourceTag<SpriteAtlas> atlasID, std::vector<SpriteInstanceData> instanceDatas);
	};
}
