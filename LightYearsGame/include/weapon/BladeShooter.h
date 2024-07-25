#pragma once
#include "SFML/Graphics.hpp"
#include "weapon/BulletShooter.h"

namespace ly
{
	class BladeShooter : public Shooter
	{
	public:
		BladeShooter(Actor* owner, 
			float cooldownTimer = 0.2f, 
			const sf::Vector2f& localOffset = { 0.f, 0.f },
			float width = 60.f
		);

		virtual void IncreaseLevel(int addLevel = 1) override;


	private:
		virtual void ShootImp() override;
		float mWidth;

		BulletShooter mShooter1;
		BulletShooter mShooter2;
		BulletShooter mShooter3;
		BulletShooter mShooter4;

		BulletShooter mShooter5;
		BulletShooter mShooter6;
	};
}