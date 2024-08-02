#include "enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"
#include "player/PlayerManager.h"

namespace ly
{
	
	EnemySpaceship::EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage, const List<RewardFactoryFunction> rewards)
		: Spaceship{ owningWorld, texturePath },
		mCollisionDamage{ collisionDamage },
		mRewards{rewards},
		mScoreReward{10}
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
	void EnemySpaceship::SetScoreAward(unsigned int amount)
	{
		mScoreReward = amount;
	}
	void EnemySpaceship::SpawnReward()
	{
		if (mRewards.size() == 0) { return; }
		int pick = (int)RandomRange(0, mRewards.size());
		if (pick >= 0 && pick < mRewards.size()) 
		{ 
			weak<Reward> newReward = mRewards[pick](GetWorld()); 
			newReward.lock()->SetActorLocation(GetActorLocation());
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
	void EnemySpaceship::DropReward()
	{
		SpawnReward();
		Player* player = PlayerManager::Get().GetPlayer();
		if (player)
		{
			player->AddScore(mScoreReward);
		}
	}
}