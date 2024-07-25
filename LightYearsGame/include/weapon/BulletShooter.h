#pragma once
#include "SFML/System.hpp"
#include "weapon/Shooter.h"

namespace ly
{
	class Actor;
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, 
			float coolDownTime =1.f, 
			const sf::Vector2f localPositionOffset = {0.f, 0.f}, 
			float localRotationOffset = 0,
			const std::string& bulletTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");


		virtual bool IsOnCooldown() const override;
		virtual void IncreaseLevel(int addLevel = 1) override;
		void SetBulletTexturePath(const std::string& bulletTexturePath);
	private:
		virtual void ShootImp() override;
		sf::Clock mCooldownClock;
		float mCooldownTime;
		sf::Vector2f mLocalPositionOffset;
		float mLocalRotationOffset;
		std::string mBulletTexturePath;
	};
}