#include "weapon/ThreeWayShooter.h"

namespace ly
{
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float cooldownTimer, const sf::Vector2f& localOffset)
		: Shooter{ owner },
		mShooterLeft{ owner, cooldownTimer, localOffset, -20.f, "SpaceShooterRedux/PNG/Lasers/laserRed16.png" },
		mShooterMid{ owner, cooldownTimer, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen06.png" },
		mShooterRight{ owner, cooldownTimer, localOffset, 20.f, "SpaceShooterRedux/PNG/Lasers/laserRed16.png" },
		mDoubleShooterLeft{ owner, cooldownTimer, localOffset, -35.f, "SpaceShooterRedux/PNG/Lasers/laserBlue02.png" },
		mDoubleShooterRight{ owner, cooldownTimer, localOffset, 35.f, "SpaceShooterRedux/PNG/Lasers/laserBlue02.png" }
	{
		
	}
	void ThreeWayShooter::IncreaseLevel(int addLevel)
	{
		Shooter::IncreaseLevel(addLevel);
		mShooterLeft.IncreaseLevel(addLevel);
		mShooterMid.IncreaseLevel(addLevel);
		mShooterRight.IncreaseLevel(addLevel);
		mDoubleShooterLeft.IncreaseLevel(addLevel);
		mDoubleShooterRight.IncreaseLevel(addLevel);
	}
	void ThreeWayShooter::ShootImp()
	{
		mShooterLeft.Shoot();
		mShooterMid.Shoot();
		mShooterRight.Shoot();

		if (GetCurrentLevel() == GetmaxLevel())
		{
			mDoubleShooterLeft.Shoot();
			mDoubleShooterRight.Shoot();
		}
	}
}