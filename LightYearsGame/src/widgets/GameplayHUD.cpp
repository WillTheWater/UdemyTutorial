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
		mGreenHealth{128,255,128,255},
		mRedHealth{255,0,0,255},
		mDangerZone{0.3f}
	{
		mFrameRateText.SetFontSize(60);
	}
	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mFrameRateText.NativeDraw(windowRef);
		mPlayerHealthBar.NativeDraw(windowRef);
	}
	void GameplayHUD::Tick(float deltaTime)
	{
		int framerate = int(1/deltaTime);
		std::string framerateText = "Framerate: " + std::to_string(framerate);
		mFrameRateText.SetString(framerateText);
	}
	void GameplayHUD::Init(const sf::RenderWindow& windowRef)
	{
		auto windowSize = windowRef.getSize();
		mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{ 15.f, windowSize.y - 50.f });
		RefreshHealthBar();
		

	}
	void GameplayHUD::PlayerHealthUpdate(float amount, float currentHealth, float maxHealth)
	{
		mPlayerHealthBar.UpdateValue(currentHealth, maxHealth);
		if (currentHealth / maxHealth < mDangerZone) { mPlayerHealthBar.SetForegroundColor(mRedHealth); }
		else { mPlayerHealthBar.SetForegroundColor(mGreenHealth); }
	}
	void GameplayHUD::RefreshHealthBar()
	{
		Player* player = PlayerManager::Get().GetPlayer(); 
		if (player && !player->GetCurrentSpaceship().expired()) 
		{
			weak<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship();
			HealthComponent& health = player->GetCurrentSpaceship().lock()->GetHealthComponent(); 
			health.onHealthChange.BindAction(GetWeakReference(), &GameplayHUD::PlayerHealthUpdate); 
			mPlayerHealthBar.UpdateValue(health.GetHealth(), health.GetMaxHealth()); 
		}
	}
	void GameplayHUD::PlayerSpaceshipDestroyed(Actor* actor)
	{
		RefreshHealthBar();
	}
}