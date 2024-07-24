#include "enemy/EnemySpaceship.h"

namespace ly
{
	EnemySpaceship::EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage)
		: Spaceship{owningWorld, texturePath},
		mCollisionDamage{collisionDamage}
	{
		SetTeamID(2);
	}
	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width) * 4.f)
		{
			Destroy();
		}
	}
	void EnemySpaceship::OnActorBeginOverlap(Actor* other)
	{
		Spaceship::OnActorBeginOverlap(other);
		if (IsEnemy(other))
		{
			other->ApplyDamage(mCollisionDamage);
		}
	}
}