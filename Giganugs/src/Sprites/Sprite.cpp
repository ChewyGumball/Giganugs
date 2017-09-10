#include "Sprites/Sprite.h"


namespace Giganugs::Sprites {
	bool Sprite::inside(float minX, float minY, float maxX, float maxY)
	{
		return (x + width > minX) && (x < maxX) && (y + height > minY) && (y < maxY);
	}
}
