#include "Sprites/SpriteAtlas.h"


#include "Util/FileUtils.h"
#include "Util/StringUtils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image/stb_image.h"

using Microsoft::WRL::ComPtr;

namespace Giganugs::Sprites {
	SpriteAtlas::SpriteAtlas(int ID, std::string_view filename, ComPtr<ID3D11Device> device)
		:ID(ID)
	{
		std::string contents = Util::File::ReadWholeFile(filename);
		std::vector<std::string_view> fileLines = Util::String::Split(contents, '\n');

		auto firstLine = Util::String::Split(fileLines[0], ' ');

		std::string imageFilename = "resources/sprites/images/" + std::string(firstLine[0]);
		int imageWidth = Util::String::svtoi(firstLine[1]);
		int imageHeight = Util::String::svtoi(firstLine[2]);

		for (int32_t i = 1; i < fileLines.size(); i++) {
			auto line = Util::String::Split(fileLines[i], ' ');

			if (line.size() > 0) {
				float x = Util::String::svtof(line[1]);
				float y = Util::String::svtof(line[2]);
				float width = Util::String::svtof(line[3]);
				float height = Util::String::svtof(line[4]);

				namesToIndices[std::string(line[0])] = i - 1;
				parts.push_back({ x, y, width, height });
			}
		}

		int width, height, channels;
		const uint8_t* data = stbi_load(imageFilename.c_str(), &width, &height, &channels, 0);

		D3D11_SUBRESOURCE_DATA imageData;
		imageData.pSysMem = data;
		imageData.SysMemPitch = sizeof(uint8_t) * channels * width;
		imageData.SysMemSlicePitch = imageData.SysMemPitch * height;

		D3D11_TEXTURE2D_DESC textureDescription = {};
		textureDescription.Width = width;
		textureDescription.Height = height;
		textureDescription.MipLevels = 1;
		textureDescription.ArraySize = 1;
		textureDescription.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDescription.SampleDesc.Count = 1;
		textureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		ComPtr<ID3D11Texture2D> texture;
		device->CreateTexture2D(&textureDescription, &imageData, &texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC viewDescription = {};
		viewDescription.Format = textureDescription.Format;
		viewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		viewDescription.Texture2D.MipLevels = textureDescription.MipLevels;

		device->CreateShaderResourceView(texture.Get(), &viewDescription, &textureView);
	}


	SpriteAtlas::~SpriteAtlas()
	{
	}

	int32_t SpriteAtlas::indexOf(const std::string& spriteName)
	{
		return namesToIndices.at(spriteName);
	}
}
