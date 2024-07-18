#pragma once
#include "spaceship/Spaceship.h"

namespace ly
{
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");

		virtual void Tick(float deltaTime) override;
		void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
		float GetSpeed() const { return mSpeed; }

	private:
		void Input();
		void UseInput(float deltaTime);
		sf::Vector2f mMove;
		float mSpeed;
	};
}