#pragma once
#include "Widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"

namespace ly
{
	class Actor;
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltaTime) override;


	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;
		void RefreshHealthBar();
		void PlayerHealthUpdate(float amount, float currentHealth, float maxHealth);
		void PlayerSpaceshipDestroyed(Actor* actor);
		TextWidget mFrameRateText;
		ValueGauge mPlayerHealthBar;
		sf::Color mGreenHealth;
		sf::Color mRedHealth;
		float mDangerZone;
	};
}