#pragma once 
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace ly
{
	class ChaosStage : public GameStage
	{
	public:
		ChaosStage(World* world);

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		void Spawnanguard();
		void SpawnBlade();
		void SpawnHexagon();
		void SpawnUFO();

		float mSpawnInterval;
		float mMinSpawnInterval;
		float mSpawnIntervalDecrement;
		float mSpawnIntervalDecrementInterval;
		float mStageDuration;

		TimerHandle mDifficultyTimerHandle;
		TimerHandle mTimer;
	};
}