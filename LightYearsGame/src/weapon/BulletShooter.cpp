#include "weapon/BulletShooter.h"
#include "framework/Core.h"

namespace ly
{
	BulletShooter::BulletShooter(Actor* owner, float coolDownTime)
		: Shooter{owner},
		mCooldownClock{},
		mCooldownTime{coolDownTime}
	{
	}
	bool BulletShooter::IsOnCooldown() const
	{
		if (mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime)
		{
			return false;
		}
		return true;
	}
	void BulletShooter::ShootImp()
	{
		mCooldownClock.restart();
		LOG("Shooting", "\n");
	}
}