#pragma once
#include "spaceship/Spaceship.h"

namespace ly
{
	class Shooter;
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");

		virtual void Tick(float deltaTime) override;
		void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
		float GetSpeed() const { return mSpeed; }
		virtual void Shoot() override;
		void SetShooter(unique<Shooter>&& newShooter);

	private:
		void Input();
		void NormalizeVector();
		void ClampInput();
		void UseInput(float deltaTime);
		sf::Vector2f mMove;
		float mSpeed;

		unique<Shooter> mShooter;
	};
}