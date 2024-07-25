#pragma once
#include <functional>
#include "framework/Actor.h"

namespace ly
{
	class PlayerSpaceship;
	class Reward;
	using RewardFunction = std::function<void(PlayerSpaceship*)>;
	using RewardFactoryFunction = std::function<weak<Reward>(World*)>;
	class Reward : public Actor
	{
	public:
		Reward(World* world, const std::string& texturePath, RewardFunction rewardFunction, float speed = 200.f);

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void OnActorBeginOverlap(Actor* otherActor) override;
		float mSpeed;
		RewardFunction mRewardFunction;
	};

	weak<Reward> CreateHealthReward(World* world);
	weak<Reward> CreateThreeWayShooterReward(World* world);
	weak<Reward> CreateBladeShooterReward(World* world);

	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunction rewardFunction);

	void RewardHealth(PlayerSpaceship* player);
	void RewardThreeWayShooter(PlayerSpaceship* player);
	void RewardBladeShooter(PlayerSpaceship* player);

}