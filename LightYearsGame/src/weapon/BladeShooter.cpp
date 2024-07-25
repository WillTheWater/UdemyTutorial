#include "weapon/BladeShooter.h"

namespace ly
{
	BladeShooter::BladeShooter(Actor* owner, float cooldownTimer, const sf::Vector2f& localOffset, float width)
		: Shooter{ owner },
		mWidth{width},
		mShooter1{ owner, cooldownTimer, { localOffset.x, localOffset.y - width/2.f }, -5.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter2{ owner, cooldownTimer, { localOffset.x, localOffset.y - width }, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue08.png" },
		mShooter3{ owner, cooldownTimer, { localOffset.x + width / 6.f , localOffset.y }, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue08.png" },
		mShooter4{ owner, cooldownTimer, { localOffset.x + width / 2.f , localOffset.y}, 5.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter5{ owner, 0.1f, { localOffset.x + width / 6.f , localOffset.y }, -15.f, "SpaceShooterRedux/PNG/Lasers/laserBlue08.png" },
		mShooter6{ owner, 0.1f, { localOffset.x + width / 2.f , localOffset.y}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" }
	{
	}
	void BladeShooter::IncreaseLevel(int addLevel)
	{
		Shooter::IncreaseLevel(addLevel);
		mShooter1.IncreaseLevel(addLevel);
		mShooter2.IncreaseLevel(addLevel);
		mShooter3.IncreaseLevel(addLevel);
		mShooter4.IncreaseLevel(addLevel);
	}
	void BladeShooter::ShootImp()
	{
		mShooter1.Shoot();
		mShooter2.Shoot();
		mShooter3.Shoot();
		mShooter4.Shoot();

		if (GetCurrentLevel() == GetmaxLevel())
		{
			mShooter5.Shoot();
			mShooter6.Shoot();
		}
	}
}