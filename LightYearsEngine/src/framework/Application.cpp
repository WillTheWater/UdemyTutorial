#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"

namespace ly
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string windowTitle, sf::Uint32 windowStyle)
		: mWindow{ sf::VideoMode(windowWidth, windowHeight), windowTitle, windowStyle },
		mTargetFramerate{ 60.f },
		mTick{},
		mCurrentWorld{ nullptr },
		mCleanCycleClock{},
		mCleanCycleIterval{2.f}
	{

	}
	void Application::Run()
	{
		mTick.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / mTargetFramerate;
		while (mWindow.isOpen())
		{
			sf::Event WindowEvent;
			while (mWindow.pollEvent(WindowEvent))
			{
				if (WindowEvent.type == sf::Event::EventType::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					QuitApplication();
				}
				else
				{
					DispatchEvent(WindowEvent);
				}
			}
			float frameDeltaTime = mTick.restart().asSeconds();
			accumulatedTime += frameDeltaTime;
			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				RenderInternal();
;			}
		}
	}
	sf::Vector2u Application::GetWindowSize() const
	{
		return mWindow.getSize();
	}
	bool Application::DispatchEvent(const sf::Event& event)
	{
		if (mCurrentWorld)
		{
			return mCurrentWorld->DispatchEvent(event);
		}
		return false;
	}
	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		if (mCurrentWorld)
		{
			mCurrentWorld->TickInternal(deltaTime);
		}

		TimerManager::Get().UpdateTimer(deltaTime);

		PhysicsSystem::Get().Step(deltaTime);
		
		if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleIterval)
		{
			mCleanCycleClock.restart();
			AssetManager::Get().CleanCycle();
			if (mCurrentWorld)
			{
				mCurrentWorld->CleanCycle();
			}

		}
		if (mPendingWorld && mPendingWorld != mCurrentWorld)
		{
			mCurrentWorld = mPendingWorld;
			mCurrentWorld->BeginPlayInternal();
		}


	}

	void Application::RenderInternal()
	{
		mWindow.clear();

		Render();

		mWindow.display();
	}

	void Application::Render()
	{
		if (mCurrentWorld)
		{
			mCurrentWorld->Render(mWindow);
		}
	}

	void Application::Tick(float deltaTime)
	{
		
	}

}

