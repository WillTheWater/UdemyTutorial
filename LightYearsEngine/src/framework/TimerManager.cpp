#include "framework/TimerManager.h"

namespace ly
{
	
	unique<TimerManager> TimerManager::timerManager{ nullptr };

	void TimerManager::UpdateTimer(float deltaTime)
	{
		for (auto iter = mTimers.begin(); iter != mTimers.end();)
		{
			if (iter->second.Expired()){ iter = mTimers.erase(iter); }
			else { iter->second.TickTime(deltaTime); ++iter; }
		}
	}

	bool operator==(const TimerHandle& lhs, const TimerHandle& rhs)
	{
		return lhs.GetTimerKey() == rhs.GetTimerKey();
	}

	void TimerManager::ClearTimer(TimerHandle timerHandle)
	{
		auto iter = mTimers.find(timerHandle);
		if (iter != mTimers.end())
		{
			iter->second.SetExpired();
		}
	}
	TimerManager::TimerManager() :mTimers{}
	{
	}
	TimerManager& TimerManager::Get()
	{
		if (!timerManager)
		{
			timerManager = std::move(unique<TimerManager>(new TimerManager{}));
		}
		return *timerManager;
	}
	Timer::Timer(weak<Object> weakReference, std::function<void()> callback, float duration, bool repeat)
		:mListener{weakReference, callback},
		mDuration{duration},
		mRepeat{repeat},
		mTimeCounter{0},
		mIsExpired{false}
	{
	}
	void Timer::TickTime(float deltaTime)
	{
		if (Expired())
		{
			return;
		}
		mTimeCounter += deltaTime;
		if (mTimeCounter >= mDuration)
		{
			mListener.second();
			if (mRepeat) { mTimeCounter = 0.f; }
			else { SetExpired(); }
		}
	}
	bool Timer::Expired() const
	{
		return mIsExpired || mListener.first.expired() || mListener.first.lock()->IsPendingDestroy();
	}
	void Timer::SetExpired()
	{
		mIsExpired = true;
	}
	unsigned int TimerHandle::mTimerKeyCounter = 0;
	TimerHandle::TimerHandle()
		: mTimerKey{GetNextTimerKey()}
	{

	}
}