#pragma once
#include "enemy/EnemySpaceship.h"

namespace ly
{
	class BulletShooter;
	class UFO : public EnemySpaceship
	{
	public:
		UFO(World* owningWorld, const sf::Vector2f& velocity, const std::string texturePath = "SpaceShooterRedux/PNG/ufoRed.png", float rotationSpeed = 30.f);

		virtual void Tick(float deltaTime) override;
	private:
		virtual void Shoot() override;

		unique<BulletShooter> mShooter1;
		unique<BulletShooter> mShooter2;
		unique<BulletShooter> mShooter3;
		float mRotationSpeed;
	};
}