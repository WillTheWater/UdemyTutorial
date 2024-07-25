#pragma once
#include "spaceship/Spaceship.h"
#include "player/Reward.h"

namespace ly
{
	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* owningWorld,
			const std::string& texturePath,
			float collisionDamage = 400.f,
			const List<RewardFactoryFunction> rewards =
			{
				CreateHealthReward,
				CreateThreeWayShooterReward,
				CreateBladeShooterReward
			}
		);

		virtual void Tick(float deltaTime);


	private:
		void SpawnReward();
		float mCollisionDamage;
		virtual void OnActorBeginOverlap(Actor* other) override;
		virtual void DropReward() override;
		List<RewardFactoryFunction> mRewards;
	};

}