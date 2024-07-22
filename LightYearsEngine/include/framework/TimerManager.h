#include "framework/Core.h"
#include "framework/Object.h"
#include <functional>

namespace ly
{
	struct Timer
	{
	public:
		Timer(weak<Object> weakReference, std::function<void()> callback, float duration, bool repeat);
		void TickTime(float deltaTime);
		bool Expired() const;
		void SetExpired();
	private:
		std::pair<weak<Object>, std::function<void()>> mListener;
		float mDuration;
		bool mRepeat;
		float mTimeCounter;
		bool mIsExpired;

	};

	class TimerManager
	{
	public:
		static TimerManager& Get();
		template<typename ClassName>
		void SetTimer(weak<Object> weakReference, void(ClassName::* callback)(), float duration, bool repeat = false)
		{
			mTimers.push_back(Timer(weakReference, [=] {(static_cast<ClassName*>(weakReference.lock().get())->*callback)(); }, duration, repeat));
		}

		void UpdateTimer(float deltaTime);

	protected:
		TimerManager();
		
	private:
		static unique<TimerManager> timerManager;
		List<Timer> mTimers;
		
		
	};
}