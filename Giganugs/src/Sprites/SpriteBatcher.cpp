#include "Sprites/SpriteBatcher.h"

#include "Sprites/SpriteAtlasPart.h"
#include "Sprites/SpriteBatch.h"

namespace Giganugs::Sprites {

	SpriteBatcher::SpriteBatcher(int maxBatchSize, Giganugs::Resources::SpriteAtlasCatalog atlasCatalog) 
		: maxBatchSize(maxBatchSize), atlasCatalog(atlasCatalog)
	{
	}


	SpriteBatcher::~SpriteBatcher()
	{
	}

	void SpriteBatcher::add(Giganugs::Resources::ResourceTag<SpriteAtlas> atlasID, SpriteInstanceData instanceData)
	{
		auto batchListEntry = batches.find(atlasID);
		if (batchListEntry == batches.end()) {
			auto atlas = atlasCatalog.get(atlasID);
			assert(atlas != nullptr);

			batchListEntry = batches.emplace(atlasID, atlas).first;
		}

		batchListEntry->second.add(instanceData);
	}
}
