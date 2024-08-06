#include "framework/Actor.h"
#include "widgets/GameplayHUD.h"
#include "player/Player.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
	GameplayHUD::GameplayHUD()
		: mFrameRateText{"Framerate: "},
		mPlayerHealthBar{},
		mPlayerIcon{ "SpaceShooterRedux/PNG/UI/playerLife2_blue.png" },
		mPlayerLivesText{""},
		mPlayerScoreIcon{ "SpaceShooterRedux/PNG/Power-ups/star_gold.png" },
		mPlayerScoreText{ "" },
		mGreenHealth{128,255,128,255},
		mRedHealth{255,0,0,255},
		mDangerZone{0.3f},
		mWidgetSpacing{10.f},
		mWinLoseText{""},
		mFinalScore{""},
		mRestartButton{"Restart"},
		mQuitButton{"Quit"}
	{
		mFrameRateText.SetFontSize(60);
		mWinLoseText.SetVisiblity(false);
		mFinalScore.SetVisiblity(false);
		mRestartButton.SetVisiblity(false);
		mQuitButton.SetVisiblity(false);
	}
	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mFrameRateText.NativeDraw(windowRef);
		mPlayerHealthBar.NativeDraw(windowRef);
		mPlayerIcon.NativeDraw(windowRef);
		mPlayerLivesText.NativeDraw(windowRef);
		mPlayerScoreIcon.NativeDraw(windowRef);
		mPlayerScoreText.NativeDraw(windowRef);
		mWinLoseText.NativeDraw(windowRef);
		mFinalScore.NativeDraw(windowRef);
		mRestartButton.NativeDraw(windowRef);
		mQuitButton.NativeDraw(windowRef);
	}
	void GameplayHUD::Tick(float deltaTime)
	{
		int framerate = int(1/deltaTime);
		std::string framerateText = "Framerate: " + std::to_string(framerate);
		mFrameRateText.SetString(framerateText);
	}
	bool GameplayHUD::HandleEvent(const sf::Event& event)
	{
		if (mRestartButton.HandleEvent(event)) { return true; }
		if (mQuitButton.HandleEvent(event)) { return true; }
		return HUD::HandleEvent(event);
	}
	void GameplayHUD::Init(const sf::RenderWindow& windowRef)
	{
		auto windowSize = windowRef.getSize();
		mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{ 15.f, windowSize.y - 50.f });
		sf::Vector2f lifeIconLocation = mPlayerHealthBar.GetWidgetLocation();
		lifeIconLocation += sf::Vector2f{ mPlayerHealthBar.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerIcon.SetWidgetLocation(lifeIconLocation);
		lifeIconLocation += sf::Vector2f{ mPlayerIcon.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerLivesText.SetWidgetLocation(lifeIconLocation);

		lifeIconLocation += sf::Vector2f{ mPlayerHealthBar.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerScoreIcon.SetWidgetLocation(lifeIconLocation);
		lifeIconLocation += sf::Vector2f{ mPlayerScoreIcon.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerScoreText.SetWidgetLocation(lifeIconLocation);


		RefreshHealthBar();
		PlayerLives();

		mWinLoseText.SetWidgetLocation({ windowSize.x / 2.f, 200.f });
		mRestartButton.SetWidgetLocation({ windowSize.x / 2.f, windowSize.y / 2.f });
		mQuitButton.SetWidgetLocation({ windowSize.x / 2.f, windowSize.y / 2.f + 100.f });
		mRestartButton.onButtonClicked.BindAction(GetWeakReference(), &GameplayHUD::RestartButtonClicked);
		mQuitButton.onButtonClicked.BindAction(GetWeakReference(), &GameplayHUD::QuitButtonClicked);
		

	}
	void GameplayHUD::PlayerHealthUpdate(float amount, float currentHealth, float maxHealth)
	{
		mPlayerHealthBar.UpdateValue(currentHealth, maxHealth);
		if (currentHealth / maxHealth < mDangerZone) { mPlayerHealthBar.SetForegroundColor(mRedHealth); }
		else { mPlayerHealthBar.SetForegroundColor(mGreenHealth); }
	}
	void GameplayHUD::PlayerLivesUpdate(int amount)
	{
		mPlayerLivesText.SetString(std::to_string(amount));
	}
	void GameplayHUD::RefreshHealthBar()
	{
		Player* player = PlayerManager::Get().GetPlayer(); 
		if (player && !player->GetCurrentSpaceship().expired()) 
		{
			weak<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship();
			HealthComponent& health = player->GetCurrentSpaceship().lock()->GetHealthComponent(); 
			health.onHealthChange.BindAction(GetWeakReference(), &GameplayHUD::PlayerHealthUpdate);
			PlayerHealthUpdate(0, health.GetHealth(), health.GetMaxHealth());
			
		}
	}
	void GameplayHUD::PlayerLives()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		if (player)
		{
			int lives = player->GetlifeCount();
			mPlayerLivesText.SetString(std::to_string(lives));
			player->onLifeChange.BindAction(GetWeakReference(), &GameplayHUD::PlayerLivesUpdate);
		}
	}
	void GameplayHUD::PlayerSpaceshipDestroyed(Actor* actor)
	{
		RefreshHealthBar();
	}

	void GameplayHUD::RestartButtonClicked()
	{
		OnRestartButtonClick.Broadcast();
	}

	void GameplayHUD::QuitButtonClicked()
	{
		OnQuitButtonClick.Broadcast();
	}

	void GameplayHUD::GameFinished(bool playerWon)
	{
		mWinLoseText.SetVisiblity(true);
		mFinalScore.SetVisiblity(true);
		mRestartButton.SetVisiblity(true);
		mQuitButton.SetVisiblity(true);


		if (playerWon){ mWinLoseText.SetString("You Win!"); }
		else { mWinLoseText.SetString("You Lose!"); }
	}

}