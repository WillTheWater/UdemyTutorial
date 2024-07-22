#pragma once
#include "spaceship/Spaceship.h"

namespace ly
{
	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage = 400.f);
		virtual void Tick(float deltaTime);


	private:
		float mCollisionDamage;
		virtual void OnActorBeginOverlap(Actor* other) override;
	};

}