#pragma once

namespace ly
{
	class Actor;
	class Shooter
	{
	public:
		void Shoot();

		virtual bool CanShoot() const { return true; }
		virtual bool IsOnCooldown() const { return false; }
		Actor* GetOwner() const {return mOwner;}

		int GetCurrentLevel() const { return mCurrentLevel; }
		int GetmaxLevel() const { return mMaxLevel; }

		virtual void IncreaseLevel(int addLevel = 1);

	protected:
		Shooter(Actor* owner);
	private:
		virtual void ShootImp() = 0;
		Actor* mOwner;

		int mCurrentLevel;
		int mMaxLevel;
	};
}