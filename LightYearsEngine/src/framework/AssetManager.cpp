#include "framework/AssetManager.h"

namespace ly
{
	unique<AssetManager> AssetManager::assetManager{ nullptr };

	AssetManager& AssetManager::Get()
	{
		if (!assetManager)
		{
			assetManager = unique<AssetManager>{new AssetManager};
		}
		return *assetManager;
	}
	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		return LoadAsset(path, mLoadTextureMap);

	}
	shared<sf::Font> AssetManager::LoadFont(const std::string& path)
	{
		return LoadAsset(path, mLoadFontMap);
	}
	void AssetManager::CleanCycle()
	{
		CleanUniqueRef(mLoadTextureMap);
		CleanUniqueRef(mLoadFontMap);
	}
	void AssetManager::SetAssetRootDirectory(const std::string& directory)
	{
		mRootDirectory = directory;
	}
	AssetManager::AssetManager() :mRootDirectory{}
	{
	}
}

