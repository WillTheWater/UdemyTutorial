#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{
	Application::Application()
		: mWindow{ sf::VideoMode(1024, 1440), "Light Years" },
		mTargetFramerate{ 60.f },
		mTick{},
		currentWorld{nullptr}
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
			accumulatedTime += mTick.restart().asSeconds();
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
		sf::RectangleShape rect{ sf::Vector2f{100, 100} };
		rect.setOrigin( 50, 50 );
		rect.setFillColor(sf::Color::Green);
		rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);
		mWindow.draw(rect);
	}

	void Application::Tick(float deltaTime)
	{
		
	}

}

