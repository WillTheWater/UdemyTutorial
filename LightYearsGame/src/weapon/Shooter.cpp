#include "weapon/Shooter.h"

namespace ly
{
	void Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCooldown())
		{
			ShootImp();
		}
	}
	Shooter::Shooter(Actor* owner)
		:mOwner{owner}
	{

	}
}