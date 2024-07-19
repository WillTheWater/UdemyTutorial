#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
	class World;
	class Application
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string windowTitle, sf::Uint32 windowStyle);
		void Run();

		template<typename WorldType>
		weak<WorldType> loadWorld();

		sf::Vector2u GetWindowSize() const;

	private:
		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Render();
		virtual void Tick(float deltaTime);

		sf::RenderWindow mWindow;
		float mTargetFramerate;
		sf::Clock mTick;

		shared<World> currentWorld;
		sf::Clock mCleanCycleClock;
		float mCleanCycleIterval;

	};

	template<typename WorldType>
	weak<WorldType> Application::loadWorld()
	{
		shared<WorldType> newWorld{ new WorldType{this} };
		currentWorld = newWorld;
		currentWorld->BeginPlayInternal();
		return newWorld;
	}

}