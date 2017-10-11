#include "Resources/Catalogs/TextureCatalog.h"


namespace Giganugs::Resources {

	TextureCatalog::TextureCatalog(std::vector<std::string> resourceLocations, Microsoft::WRL::ComPtr<ID3D11Device> device)
		:ResourceCatalog<Graphics::Texture>(resourceLocations), device(device)
	{
	}


	TextureCatalog::~TextureCatalog()
	{
	}

	Graphics::Texture* Giganugs::Resources::TextureCatalog::create(const std::string & filename, uint32_t ID)
	{
		return new Graphics::Texture(ID, filename, device);
	}

	bool Giganugs::Resources::TextureCatalog::reload(const std::string & filename, Graphics::Texture& resource)
	{
		return resource.reload(filename, device);
	}
}
