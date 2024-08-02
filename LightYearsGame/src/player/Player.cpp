#include "player/Player.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
	Player::Player()
		: mLifeCount{3},
		mScore{0},
		mCurrentPlayerSpaceship{}
	{
	}
	weak<PlayerSpaceship> Player::SpawnPlayerSpaceship(World* world)
	{
		if (mLifeCount > 0)
		{
			--mLifeCount;
			auto windowSize = world->GetWindowSize();
			mCurrentPlayerSpaceship = world->SpawnActor<PlayerSpaceship>();
			mCurrentPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(windowSize.x/2.f, windowSize.y - 100.f));
			mCurrentPlayerSpaceship.lock()->SetActorRotation(0.f);
			onLifeChange.Broadcast(mLifeCount);
			return mCurrentPlayerSpaceship;
		}
		else
		{
			mCurrentPlayerSpaceship = weak<PlayerSpaceship>{};
			onPlayerDeath.Broadcast();
		}
		return weak<PlayerSpaceship>{};
	}
	void Player::AddLifeCount(unsigned int lives)
	{
		if (lives > 0) { mLifeCount += lives; onLifeChange.Broadcast(mLifeCount); }
	}
	void Player::AddScore(unsigned int score)
	{
		if (score > 0)
		{
			mScore = score;
			onScoreChange.Broadcast(mScore);
		}

	}
}