#pragma once
#include "SFML/System.hpp"
#include "weapon/Shooter.h"

namespace ly
{
	class Actor;
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, float coolDownTime =1.f, const sf::Vector2f localPositionOffset = {0.f, 0.f}, float localRotationOffset = 0);
		virtual bool IsOnCooldown() const override;
	private:
		virtual void ShootImp() override;
		sf::Clock mCooldownClock;
		float mCooldownTime;
		sf::Vector2f mLocalPositionOffset;
		float mLocalRotationOffset;
	};
}