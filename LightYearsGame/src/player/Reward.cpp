#include "player/Reward.h"
#include "player/PlayerSpaceship.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/BladeShooter.h"
#include "framework/World.h"
#include "player/PlayerManager.h"


namespace ly
{
	Reward::Reward(World* world, const std::string& texturePath, RewardFunction rewardFunction, float speed)
		: Actor{world, texturePath},
		mRewardFunction{rewardFunction},
		mSpeed{speed}
	{
	}
	void Reward::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}
	void Reward::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset({ 0.f, mSpeed * deltaTime });
	}
	void Reward::OnActorBeginOverlap(Actor* otherActor)
	{
		if (!otherActor || otherActor->IsPendingDestroy()) { return; }
		if (!PlayerManager::Get().GetPlayer()) { return; }
		weak<PlayerSpaceship> playerSpaceship = PlayerManager::Get().GetPlayer()->GetCurrentSpaceship();
		if (playerSpaceship.expired() || playerSpaceship.lock()->IsPendingDestroy()) { return; }
		if (playerSpaceship.lock()->GetUniqueID() == otherActor->GetUniqueID())
		{
			mRewardFunction(playerSpaceship.lock().get());
			Destroy();
		}

	}
	weak<Reward> CreateHealthReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/pill_red.png", RewardHealth);
	}
	weak<Reward> CreateThreeWayShooterReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/powerupGreen_star.png", RewardThreeWayShooter);
	}
	weak<Reward> CreateBladeShooterReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/powerupRed_star.png", RewardBladeShooter);
	}
	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunction rewardFunction)
	{
		weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunction);
		return reward;
	}
	void RewardHealth(PlayerSpaceship* player)
	{
		static float rewardHealth = 25.f;
		if(player && !player->IsPendingDestroy())
		{
			player->GetHealthComponent().ChangeHealth(rewardHealth);
		}
	}
	void RewardThreeWayShooter(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{new ThreeWayShooter{ player }});
		}
	}
	void RewardBladeShooter(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{new BladeShooter{ player }});
		}
	}
}