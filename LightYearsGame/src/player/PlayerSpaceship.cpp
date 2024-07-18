#include "player/PlayerSpaceship.h"
#include "SFML/System.hpp"

namespace ly
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
		: Spaceship{ owningWorld, path },
		mMove{},
		mSpeed{ 200.f }
	{
	}
	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		Input();
		UseInput(deltaTime);

	}
	void PlayerSpaceship::Input()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			mMove.y = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			mMove.y = 1.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			mMove.x = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			mMove.x = 1.f;
		}
	}
	void PlayerSpaceship::UseInput(float deltaTime)
	{
		SetVelocity(mMove * mSpeed);
		mMove.x = mMove.y = 0.f;
	}
}