#include "levels/GameLevelOne.h"
#include "enemy/Vanguard.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/VanguardStage.h"
#include "enemy/HexagonStage.h"
#include "enemy/UFOStage.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "framework/World.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "player/PlayerSpaceship.h"
#include "player/PlayerManager.h"





namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World{owningApp}
	{

	}
	void GameLevelOne::BeginPlay()
	{
		Player newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceship = newPlayer.SpawnPlayerSpaceship(this);
		mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakReference(), &GameLevelOne::PlayerSpaceshipDestroyed);
	}

	void GameLevelOne::PlayerSpaceshipDestroyed(Actor* playerDeath)
	{
		mPlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnPlayerSpaceship(this); 
		if (!mPlayerSpaceship.expired())
		{
			mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakReference(), &GameLevelOne::PlayerSpaceshipDestroyed);

		}
		else { GameOver(); }
	}

	void GameLevelOne::GameOver()
	{
		LOG("============================    Game Over    =============================", "\n");
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<UFOStage>{new UFOStage{ this }});
		AddStage(shared<WaitStage>{new WaitStage{ this, 3.f }});

		AddStage(shared<HexagonStage>{new HexagonStage{ this }});
		AddStage(shared<WaitStage>{new WaitStage{ this, 3.f }});
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});
		AddStage(shared<WaitStage>{new WaitStage{ this, 9.f }});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});
	}
}
