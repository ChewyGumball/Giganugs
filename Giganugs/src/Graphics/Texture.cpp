#include "Graphics/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image/stb_image.h"


namespace Giganugs::Graphics {
	Texture::Texture(uint32_t ID, const std::string& filename, Microsoft::WRL::ComPtr<ID3D11Device> device)
		: Resource(ID)
	{
		reload(filename, device);
	}


	Texture::~Texture()
	{
	}

	int32_t Texture::width() const
	{
		return m_width;
	}

	int32_t Texture::height() const
	{
		return m_height;
	}

	const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Texture::view() const
	{
		return textureView;
	}

	void Texture::reload(const std::string & filename, Microsoft::WRL::ComPtr<ID3D11Device> device)
	{
		int channels;
		uint8_t* data = stbi_load(filename.c_str(), &m_width, &m_height, &channels, 0);

		D3D11_SUBRESOURCE_DATA imageData;
		imageData.pSysMem = data;
		imageData.SysMemPitch = sizeof(uint8_t) * channels * m_width;
		imageData.SysMemSlicePitch = imageData.SysMemPitch * m_height;

		D3D11_TEXTURE2D_DESC textureDescription = {};
		textureDescription.Width = m_width;
		textureDescription.Height = m_height;
		textureDescription.MipLevels = 1;
		textureDescription.ArraySize = 1;
		textureDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDescription.SampleDesc.Count = 1;
		textureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		device->CreateTexture2D(&textureDescription, &imageData, &texturePointer);

		stbi_image_free(data);

		D3D11_SHADER_RESOURCE_VIEW_DESC viewDescription = {};
		viewDescription.Format = textureDescription.Format;
		viewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		viewDescription.Texture2D.MipLevels = textureDescription.MipLevels;

		device->CreateShaderResourceView(texturePointer.Get(), &viewDescription, &textureView);
	}
}
