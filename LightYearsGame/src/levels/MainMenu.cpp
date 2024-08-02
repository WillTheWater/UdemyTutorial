#include "levels/MainMenu.h"
#include "widgets/MainMenuHud.h"
#include "framework/Application.h"
#include "levels/GameLevelOne.h"

namespace ly
{
	MainMenu::MainMenu(Application* owningApplication)
		: World{owningApplication}
	{
		mMainMenuHUD = SpawnHUD<MainMenuHUD>();
	}
	void MainMenu::BeginPlay()
	{
		mMainMenuHUD.lock()->OnStartButtonClick.BindAction(GetWeakReference(), &MainMenu::StartGame);
		mMainMenuHUD.lock()->OnQuitButtonClick.BindAction(GetWeakReference(), &MainMenu::QuitGame);
	}
	void MainMenu::StartGame()
	{
		GetApplication()->loadWorld<GameLevelOne>();
	}
	void MainMenu::QuitGame()
	{
		GetApplication()->QuitApplication();
	}
}