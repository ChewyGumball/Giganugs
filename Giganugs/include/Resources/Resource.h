#pragma once
#include "Resources/ResourceTag.h"

namespace Giganugs::Resources {
template <class T>
	class Resource
	{
	public:
		const ResourceTag<T> tag;
		Resource(uint32_t ID) : tag(ID) {}
	};
}