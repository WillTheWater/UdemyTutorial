#pragma once
#include "SFML/Graphics.hpp"
#include "framework/Core.h"

namespace ly
{
	class AssetManager
	{
	public:
		static AssetManager& Get();
		shared<sf::Texture> LoadTecture(const std::string& path);
		void CleanCycle();
		void SetAssetRootDirectory(const std::string& directory);

	protected:
		AssetManager();

	private:
		static unique<AssetManager> assetManager;
		Dictionary<std::string, shared<sf::Texture>> mLoadTextureMap;
		std::string mRootDirectory;

	};
}