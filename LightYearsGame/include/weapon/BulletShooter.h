#pragma once
#include "SFML/System.hpp"
#include "weapon/Shooter.h"

namespace ly
{
	class Actor;
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, float coolDownTime =1.f);
		virtual bool IsOnCooldown() const override;
	private:
		virtual void ShootImp() override;
		sf::Clock mCooldownClock;
		float mCooldownTime;
	};
}