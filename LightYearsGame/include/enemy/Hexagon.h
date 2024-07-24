#pragma once
#include "enemy/EnemySpaceship.h"

namespace ly
{
	class BulletShooter;
	class Hexagon : public EnemySpaceship
	{
	public:
		Hexagon(World* owningworld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue4.png", const sf::Vector2f& velocity = { 0.f, 70.f });

		virtual void Tick(float deltaTime) override;
	private:
		virtual void Shoot() override;

		unique<BulletShooter> mShooter1;
		unique<BulletShooter> mShooter2;
		unique<BulletShooter> mShooter3;
		unique<BulletShooter> mShooter4;
		unique<BulletShooter> mShooter5;
		unique<BulletShooter> mShooter6;

	};
}