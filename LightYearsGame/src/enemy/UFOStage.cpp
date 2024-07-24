#include "enemy/UFOStage.h"
#include "enemy/UFO.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ly
{
	UFOStage::UFOStage(World* world)
		: GameStage{world},
		mSpawnInterval{4.f},
		mSpawnAmount{10},
		mCurrentSpawnAmount{0},
		mUFOSpeed{170}
	{
	}
	void UFOStage::StartStage()
	{
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakReference(), &UFOStage::SpawnUFO, mSpawnInterval, true);
	}

	void UFOStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimer);
	}

	sf::Vector2f UFOStage::GetRandomSpawnLocation() const
	{
		auto windowSize = GetWorld()->GetWindowSize();
		float spawnLeft = RandomRange(-1, 1);
		float spawnX = 0;
		if (spawnLeft < 0) { spawnX = windowSize.x + 100.f; }
		else { spawnX = -100.f; }

		float spawnY = RandomRange(0, windowSize.y);
		return sf::Vector2f{ spawnX, spawnY };
	}

	void UFOStage::SpawnUFO()
	{
		sf::Vector2f spawnLocation = GetRandomSpawnLocation();
		auto windowSize = GetWorld()->GetWindowSize();
		sf::Vector2f center{ windowSize.x / 2.f, windowSize.y / 2.f };
		sf::Vector2f moveTooCenter{center.x - spawnLocation.x, center.y - spawnLocation.y};
		Normalize(moveTooCenter);

		sf::Vector2f spawnSpeed = moveTooCenter * mUFOSpeed;

		weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(spawnSpeed);
		newUFO.lock()->SetActorLocation(spawnLocation);

		if (++mCurrentSpawnAmount == mSpawnAmount){	FinishStage(); }
	
	}
	
}