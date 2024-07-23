#include "enemy/VanguardStage.h"
#include "enemy/Vanguard.h"
#include "enemy/TwinBlade.h"
#include "framework/World.h"

namespace ly
{
	VanguardStage::VanguardStage(World* world)
		: GameStage{world},
		mSpawnInterval{1.f},
		mSwitchInterval{2.f},
		mSpawnDistanceToEdge{100.f},
		mLeftSpawnLocation{0.f, 0.f},
		mRightSpawnLocation{0.f, 0.f},
		mSpawnLocation{0.f, 0.f},
		mRowsToSpawn{2},
		mRowSpawnCount{0},
		mVanguardsPerRow{1},
		mCurrentVanguardCount{0}
	{
	}
	void VanguardStage::StartStage()
	{
		auto windowSize = GetWorld()->GetWindowSize();
		mLeftSpawnLocation = sf::Vector2f{ mSpawnDistanceToEdge, -100.f };
		mRightSpawnLocation = sf::Vector2f{ windowSize.x - mSpawnDistanceToEdge, -100.f };

		SwitchRow();
	}
	void VanguardStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimerHandle);
		TimerManager::Get().ClearTimer(mSwitchTimerHandle);
	}
	void VanguardStage::SpawnVanguard()
	{
		weak<TwinBlade> newVanguard = GetWorld()->SpawnActor<TwinBlade>();
		newVanguard.lock()->SetActorLocation(mSpawnLocation);
		++mCurrentVanguardCount;
		if (mCurrentVanguardCount == mVanguardsPerRow) 
		{ 
			TimerManager::Get().ClearTimer(mSpawnTimerHandle); 
			mSwitchTimerHandle = TimerManager::Get().SetTimer(GetWeakReference(), &VanguardStage::SwitchRow, mSwitchInterval, false);
			mCurrentVanguardCount = 0;
		}
	}
	void VanguardStage::SwitchRow()
	{
		if (mRowSpawnCount == mRowsToSpawn) { FinishStage(); return; }
		if (mSpawnLocation == mLeftSpawnLocation) { mSpawnLocation = mRightSpawnLocation; }
		else { mSpawnLocation = mLeftSpawnLocation; }

		mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakReference(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);
		++mRowSpawnCount;

	}
}