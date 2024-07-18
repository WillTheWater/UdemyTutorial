#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceship.h"
#include "config.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication()
		:Application{600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		weak<World> newWorld = loadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();
		testPlayer = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		testPlayer.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		testPlayer.lock()->SetActorRotation(0.f);
	}

	void GameApplication::Tick(float deltaTime)
	{
		
	}
}