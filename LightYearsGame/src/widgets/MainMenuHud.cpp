#include "Widgets/MainMenuHud.h"


namespace ly
{
	MainMenuHUD::MainMenuHUD()
		: mTitleText{"Space Shooter"},
		mStartButton{"Start"},
		mQuitButton{"Quit"}
	{
		mTitleText.SetFontSize(120);
		mStartButton.SetButtonFontSize(40);
		mQuitButton.SetButtonFontSize(40);
	}
	void MainMenuHUD::Draw(sf::RenderWindow& windowRef)
	{
		mTitleText.NativeDraw(windowRef);
		mStartButton.NativeDraw(windowRef);
		mQuitButton.NativeDraw(windowRef);
	}
	bool MainMenuHUD::HandleEvent(const sf::Event& event)
	{
		return mStartButton.HandleEvent(event) || mQuitButton.HandleEvent(event) || HUD::HandleEvent(event);
	}
	void MainMenuHUD::Init(const sf::RenderWindow& windowRef)
	{
		sf::Vector2u windowSize = windowRef.getSize();
		mTitleText.SetWidgetLocation({windowSize.x / 2.f, 200.f});
		mStartButton.SetWidgetLocation({ windowSize.x / 2.f, windowSize.y / 2.f });
		mQuitButton.SetWidgetLocation({ windowSize.x / 2.f, windowSize.y / 2.f + 100.f });
		mStartButton.onButtonClicked.BindAction(GetWeakReference(), &MainMenuHUD::StartButtonClicked);
		mQuitButton.onButtonClicked.BindAction(GetWeakReference(), &MainMenuHUD::QuitButtonClicked);
	}
	void MainMenuHUD::StartButtonClicked()
	{
		OnStartButtonClick.Broadcast();
	}
	void MainMenuHUD::QuitButtonClicked()
	{
		OnQuitButtonClick.Broadcast();
	}
}