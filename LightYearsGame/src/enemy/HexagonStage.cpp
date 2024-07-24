#include "enemy/HexagonStage.h"
#include "enemy/Hexagon.h"
#include "framework/World.h"

namespace ly
{
	HexagonStage::HexagonStage(World* world)
		: GameStage{world},
		mSpawnInterval{4.f},
		mSpawnOffset{90.f},
		mSpawnGroup{2},
		mCurrentSpawnCount{0},
		mMidSpawnLocation{world->GetWindowSize().x/2.f, -100.f},
		mLeftSpawnLocation{world->GetWindowSize().x/2 - mSpawnOffset, -100.f - mSpawnOffset },
		mRightSpawnLocation{world->GetWindowSize().x/2 + mSpawnOffset, -100.f - mSpawnOffset}
	{
	}
	void HexagonStage::StartStage()
	{
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakReference(), &HexagonStage::SpawnHexagon, mSpawnInterval, true);
	}
	void HexagonStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimer);
	}
	void HexagonStage::SpawnHexagon()
	{
		weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(mMidSpawnLocation);

		newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(mLeftSpawnLocation);

		newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(mRightSpawnLocation);

		if (++mCurrentSpawnCount == mSpawnGroup)
		{
			StageFinished();
		}
	}
}