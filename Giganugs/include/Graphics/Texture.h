#pragma once
#include <d3d11.h>
#include <string>
#include <wrl.h>

#include "Resources/Resource.h"

namespace Giganugs::Graphics {
	class Texture : public Resources::Resource<Texture>
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> texturePointer;

		int32_t m_width;
		int32_t m_height;

	public:
		Texture(uint32_t ID, const std::string& filename, Microsoft::WRL::ComPtr<ID3D11Device> device);
		~Texture();

		int32_t width() const;
		int32_t height() const;
		const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> view() const;
		void reload(const std::string& filename, Microsoft::WRL::ComPtr<ID3D11Device> device);
	};
}
