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
	shared<sf::Texture> AssetManager::LoadTecture(const std::string& path)
	{
		auto found = mLoadTextureMap.find(path);
		if (found != mLoadTextureMap.end())
		{
			return found->second;
		}

		shared<sf::Texture> newTexture{ new sf::Texture };
		if (newTexture->loadFromFile(path))
		{
			mLoadTextureMap.insert({ path, newTexture });
			return newTexture;
		}

		return shared<sf::Texture> {nullptr };

	}
	void AssetManager::CleanCycle()
	{
		for (auto iter = mLoadTextureMap.begin(); iter != mLoadTextureMap.end();)
		{
			if (iter->second.unique())
			{
				LOG("Cleaning Textures", "\n");
				iter = mLoadTextureMap.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
	AssetManager::AssetManager()
	{
	}
}

