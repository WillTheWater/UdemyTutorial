#pragma once
#include "SFML/Graphics.hpp"
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace ly
{
	class TwinBladeStage : public GameStage
	{
	public:
		TwinBladeStage(World* world);
		virtual void StartStage() override;

	
	private:
		float mSpawnInterval;
		float mSpawnDistanceToCenter;

		sf::Vector2f mLeftSpawnLocation;
		sf::Vector2f mRightSpawnLocation;
		sf::Vector2f mSpawnLocation;

		TimerHandle mSpawnTimerHandle;
		
		int mSpawnCount;
		int mCurrentSpawnCount;

		virtual void StageFinished() override;
		void SpawnTwinBlade();
		
	};
}