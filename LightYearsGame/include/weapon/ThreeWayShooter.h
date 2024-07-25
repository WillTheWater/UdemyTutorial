#pragma once
#include "SFML/Graphics.hpp"
#include "weapon/BulletShooter.h"

namespace ly
{
	class ThreeWayShooter : public Shooter
	{
	public:
		ThreeWayShooter(Actor* owner, float cooldownTimer = 0.2f, const sf::Vector2f& localOffset = { 0.f, 0.f });

		BulletShooter mShooterLeft;
		BulletShooter mShooterMid;
		BulletShooter mShooterRight;

		BulletShooter mDoubleShooterLeft;
		BulletShooter mDoubleShooterRight;

		virtual void IncreaseLevel(int addLevel = 1) override;


	private:
		virtual void ShootImp() override;
	};
}