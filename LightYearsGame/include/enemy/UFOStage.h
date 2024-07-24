#pragma once
#include "SFML/Graphics.hpp"
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
	class UFOStage : public GameStage
	{
	public:
		UFOStage(World* world);
		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		sf::Vector2f GetRandomSpawnLocation() const;
		void SpawnUFO();

		float mSpawnInterval;
		int mSpawnAmount;
		int mCurrentSpawnAmount;
		float mUFOSpeed;

		TimerHandle mSpawnTimer;
	};

}