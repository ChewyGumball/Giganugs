#pragma once

namespace Giganugs::Sprites {
	struct SpriteAtlasPart
	{
		float x;
		float y;
		float width;
		float height;
	};

	struct SpriteInstanceData {
		float x, y, z;
		SpriteAtlasPart atlasData;
	};
}
