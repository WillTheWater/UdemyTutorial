#include "enemy/TwinBladeStage.h"
#include "enemy/TwinBlade.h"
#include "framework/World.h"

namespace ly
{
	TwinBladeStage::TwinBladeStage(World* world)
		: GameStage{world},
		mSpawnInterval{1.5f},
		mSpawnDistanceToCenter{100.f},
		mLeftSpawnLocation{world->GetWindowSize().x/2 - mSpawnDistanceToCenter, -100.f},
		mRightSpawnLocation{world->GetWindowSize().x/2 + mSpawnDistanceToCenter, -100.f},
		mSpawnLocation{mLeftSpawnLocation},
		mSpawnCount{10},
		mCurrentSpawnCount{}

	{
	}
	void TwinBladeStage::StartStage()
	{
		mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakReference(), &TwinBladeStage::SpawnTwinBlade, mSpawnInterval, true);
	}
	void TwinBladeStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimerHandle);
	}
	void TwinBladeStage::SpawnTwinBlade()
	{
		weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
		newTwinBlade.lock()->SetActorLocation(mSpawnLocation);
		if (mSpawnLocation == mLeftSpawnLocation) { mSpawnLocation = mRightSpawnLocation; }
		else { mSpawnLocation = mLeftSpawnLocation; }
		++mCurrentSpawnCount;
		if (mCurrentSpawnCount == mSpawnCount) { FinishStage(); }
	}
}