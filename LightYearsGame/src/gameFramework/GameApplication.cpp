#include "gameFramework/GameApplication.h"
#include "levels/GameLevelOne.h"
#include "framework/AssetManager.h"
#include "config.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication()
		:Application{1200, 1960, "Light Years", sf::Style::Titlebar | sf::Style::Close}
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		weak<GameLevelOne> newWorld = loadWorld<GameLevelOne>();
	}
	//	ORIGINAL	:Application{600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}

}