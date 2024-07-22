#include "levels/GameLevelOne.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceship.h"
#include "enemy/Vanguard.h"
#include "framework/TimerManager.h"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World{owningApp}
	{
		testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		testPlayerSpaceship.lock()->SetActorRotation(0.f);

		weak<Vanguard> testShip = SpawnActor<Vanguard>();
		testShip.lock()->SetActorLocation(sf::Vector2f(100.f, 290.f));

	}
	void GameLevelOne::BeginPlay()
	{
		TimerManager::Get().SetTimer(GetWeakReference(), &GameLevelOne::TimerCallback_Test, 1.f, true);
	}
	void GameLevelOne::TimerCallback_Test()
	{
		LOG("Game Timer Called", "\n");
	}
}
