#pragma once
#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly
{
	class PlayerSpaceship;
	class World;
	class Player : public Object
	{
	public:
		Player();
		weak<PlayerSpaceship> SpawnPlayerSpaceship(World* world);
		const weak<PlayerSpaceship> GetCurrentSpaceship() const { return mCurrentPlayerSpaceship; }

		void AddLifeCount(unsigned int lives);
		int GetlifeCount() const { return mLifeCount; }
		void AddScore(unsigned int score);
		int GetScore() const { return mScore; }

		Delegate<int> onLifeChange;
		Delegate<int> onScoreChange;
		Delegate<> onPlayerDeath;
	private:
		unsigned int mLifeCount;
		unsigned int mScore;
		weak<PlayerSpaceship> mCurrentPlayerSpaceship;
	};

}