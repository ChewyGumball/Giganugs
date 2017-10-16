#pragma once

#include <wrl.h>
#include <d3d11.h>

#include "Graphics/Texture.h"
#include "Resources/ResourceCatalog.h"

namespace Giganugs::Resources {
	class TextureCatalog : public ResourceCatalog<Graphics::Texture>
	{
	private: 
		Microsoft::WRL::ComPtr<ID3D11Device> device;
	public:
		TextureCatalog(const std::vector<std::string>& resourceLocations, Microsoft::WRL::ComPtr<ID3D11Device> device);
		virtual ~TextureCatalog() override;

	protected:
		// Inherited via ResourceCatalog
		virtual Graphics::Texture* create(const std::string & filename, uint32_t ID) override;
		virtual bool reload(const std::string & filename, Graphics::Texture& resource) override;
	};
}
