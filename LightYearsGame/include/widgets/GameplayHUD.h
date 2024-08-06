#pragma once
#include "Widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"
#include "widgets/ImageWidget.h"
#include "widgets/Button.h"

namespace ly
{
	class Actor;
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltaTime) override;
		virtual bool HandleEvent(const sf::Event& event) override;
		void GameFinished(bool playerWon);
		Delegate<> OnRestartButtonClick;
		Delegate<> OnQuitButtonClick;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;
		void RefreshHealthBar();
		void PlayerLives();
		void PlayerHealthUpdate(float amount, float currentHealth, float maxHealth);
		void PlayerLivesUpdate(int amount);
		void PlayerSpaceshipDestroyed(Actor* actor);
		void RestartButtonClicked();
		void QuitButtonClicked();
		TextWidget mFrameRateText;
		ValueGauge mPlayerHealthBar;
		ImageWidget mPlayerIcon;
		TextWidget mPlayerLivesText;

		ImageWidget mPlayerScoreIcon;
		TextWidget mPlayerScoreText;

		

		sf::Color mGreenHealth;
		sf::Color mRedHealth;
		float mDangerZone;
		float mWidgetSpacing;

		TextWidget mWinLoseText;
		TextWidget mFinalScore;
		Button mRestartButton;
		Button mQuitButton;

	};
}