#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string windowTitle, sf::Uint32 windowStyle)
		: mWindow{ sf::VideoMode(windowWidth, windowHeight), windowTitle, windowStyle },
		mTargetFramerate{ 60.f },
		mTick{},
		currentWorld{ nullptr }
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
				if (WindowEvent.type == sf::Event::EventType::Closed)
				{
					mWindow.close();
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
	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		if (currentWorld)
		{
			currentWorld->TickInternal(deltaTime);
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
		if (currentWorld)
		{
			currentWorld->Render(mWindow);
		}
	}

	void Application::Tick(float deltaTime)
	{
		
	}

}

