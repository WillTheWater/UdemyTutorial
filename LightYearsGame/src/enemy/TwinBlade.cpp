#include "enemy/TwinBlade.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	TwinBlade::TwinBlade(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceship{owningWorld, texturePath},
		mShooterLeft{ new BulletShooter{ this, 1.f, {50.f, -140.f}} },
		mShooterRight{new BulletShooter{ this, 1.f, {50.f, 40.f}} }
	{
		SetVelocity(velocity);
		SetActorRotation(180.f);
	}
	void TwinBlade::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}
	void TwinBlade::Shoot()
	{
		mShooterLeft->Shoot();
		mShooterRight->Shoot();
	}
}