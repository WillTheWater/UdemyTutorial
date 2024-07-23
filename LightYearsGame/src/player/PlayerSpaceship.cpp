#include "player/PlayerSpaceship.h"
#include "SFML/System.hpp"
#include "framework/MathUtility.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
		: Spaceship{ owningWorld, path },
		mMove{},
		mSpeed{ 200.f },
		mShooter{ new BulletShooter{this, 0.2f, {50.f, 0.f}} }
	{
		SetTeamID(1);
	}
	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		Input();
		UseInput(deltaTime);

	}
	void PlayerSpaceship::Shoot()
	{
		if (mShooter)
		{
			mShooter->Shoot();
		}

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

		ClampInput();

		NormalizeVector();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Shoot();
		}
	}
	void PlayerSpaceship::NormalizeVector()
	{
		Normalize(mMove);
	}
	void PlayerSpaceship::ClampInput()
	{
		sf::Vector2f actorLocation = GetActorLocation();
		if (actorLocation.x < 0 && mMove.x == -1.f)
		{
			mMove.x = 0.f;
		}
		if (actorLocation.x > GetWindowSize().x && mMove.x == 1.f)
		{
			mMove.x = 0.f;
		}
		if (actorLocation.y < 0 && mMove.y == -1.f)
		{
			mMove.y = 0.f;
		}
		if (actorLocation.y > GetWindowSize().y && mMove.y == 1.f)
		{
			mMove.y = 0.f;
		}
	}
	void PlayerSpaceship::UseInput(float deltaTime)
	{
		SetVelocity(mMove * mSpeed);
		mMove.x = mMove.y = 0.f;
	}
}