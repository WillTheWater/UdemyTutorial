#pragma once
#include "enemy/EnemySpaceship.h"

namespace ly
{
	class BulletShooter;
	class TwinBlade : public EnemySpaceship
	{
	public:
		TwinBlade(World* owningWorld,
			const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue2.png",
			const sf::Vector2f& velocity = { 0.f, 50.f });
		virtual void Tick(float deltaTime) override;
		virtual void Shoot() override;

	private:
		unique<BulletShooter> mShooterLeft;
		unique<BulletShooter> mShooterRight;

	};
}