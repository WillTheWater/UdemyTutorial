#include "levels/GameLevelOne.h"
#include "enemy/Vanguard.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/VanguardStage.h"
#include "enemy/HexagonStage.h"
#include "enemy/UFOStage.h"
#include "framework/Actor.h"
#include "framework/BackdropActor.h"
#include "framework/AssetManager.h"
#include "framework/Application.h"
#include "framework/TimerManager.h"
#include "framework/World.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "player/PlayerSpaceship.h"
#include "player/PlayerManager.h"
#include "widgets/GameplayHUD.h"





namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World{owningApp}
	{

	}
	void GameLevelOne::AllGameStagesFinished()
	{
		mGameplayHUD.lock()->GameFinished(true);
	}
	void GameLevelOne::BeginPlay()
	{
		SpawnCosmetics();
		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceship = newPlayer.SpawnPlayerSpaceship(this);
		mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakReference(), &GameLevelOne::PlayerSpaceshipDestroyed);
		mGameplayHUD = SpawnHUD<GameplayHUD>();
		mGameplayHUD.lock()->OnQuitButtonClick.BindAction(GetWeakReference(), &GameLevelOne::QuitGame);
		mGameplayHUD.lock()->OnRestartButtonClick.BindAction(GetWeakReference(), &GameLevelOne::Restart);
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
		mGameplayHUD.lock()->GameFinished(false);
	}

	void GameLevelOne::InitGameStages()
	{

		AddStage(shared<UFOStage>{new UFOStage{ this }});
		AddStage(shared<UFOStage>{new UFOStage{ this }});
		AddStage(shared<WaitStage>{new WaitStage{ this, 1.f }});
		AddStage(shared<HexagonStage>{new HexagonStage{ this }});
		AddStage(shared<HexagonStage>{new HexagonStage{ this }});
		AddStage(shared<WaitStage>{new WaitStage{ this, 1.f }});
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});
		AddStage(shared<WaitStage>{new WaitStage{ this, 1.f }});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});
	}
	void GameLevelOne::QuitGame()
	{
		GetApplication()->QuitApplication();
	}
	void GameLevelOne::Restart()
	{
		GetApplication()->loadWorld<GameLevelOne>();
	}
	void GameLevelOne::SpawnCosmetics()
	{
		auto backdropActor = SpawnActor<BackdropActor>("SpaceShooterRedux/Backgrounds/darkPurple.png");
	}
}
