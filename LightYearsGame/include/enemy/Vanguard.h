#pragma once
#include "enemy/EnemySpaceship.h"


namespace ly
{
	class BulletShooter;
	class Vanguard : public EnemySpaceship
	{
	public:
		Vanguard(World* owningWorld, 
			const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack3.png", 
			const sf::Vector2f& velocity = {0.f, 30.f});
		virtual void Tick(float deltaTime) override;

	private:
		virtual void Shoot() override;
		unique<BulletShooter> mShooter;
		
	};
}