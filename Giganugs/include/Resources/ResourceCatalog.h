#pragma once
#include <assert.h>
#include <functional>
#include <fstream>
#include <unordered_map>

#include "Util/FileUtils.h"
#include "Resources/ResourceTag.h"

namespace Giganugs::Resources {
	template <class T>
	class ResourceCatalog
	{
	private:
		uint32_t nextID = 0;
		std::vector<std::string> resourceLocations; 
		std::unordered_map<std::string, ResourceTag<T>> resourceNames;
		std::unordered_map<ResourceTag<T>, T*> resources;

	protected:
		virtual T* create(const std::string& filename, uint32_t ID) = 0;
		virtual bool reload(const std::string& filename, T& resource) = 0;

	public:
		ResourceCatalog(std::vector<std::string> resourceLocations) 
		: resourceLocations(resourceLocations) { }

		virtual ~ResourceCatalog() {
			for (auto& resource : resources) {
				delete resource.second;
			}
		}

		T* locate(const std::string& resourceName) {
			if (resourceNames.count(resourceName) == 0) {
				bool found = false;
				for (auto& path : resourceLocations) {
					std::string location = path + "/" + resourceName;
					if (std::ifstream(location)) {
						T* resource = create(location, ++nextID);
						ResourceTag<T> tag = resource->tag;
						resources[tag] = resource;
						resourceNames[resourceName] = tag;

						Util::File::WatchForChanges(location, [=]() -> bool { return this->reload(location, *resources[tag]); });
						found = true;
						break;
					}
				}

				assert(found);
			}

			return resources[resourceNames[resourceName]];
		}

		T* get(const ResourceTag<T>& tag) {
			if (resources.count(tag) == 0) {
				return nullptr;
			}
			else {
				return resources[tag];
			}
		}
	};
}
