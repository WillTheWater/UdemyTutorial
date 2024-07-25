#include "spaceship/Spaceship.h"
#include "framework/MathUtility.h"
#include "VFX/Explosion.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{ owningWorld, texturePath },
		mVelocity{},
		mHealthComponent{100.f, 100.f},
		mBlinkTime{0.f},
		mBlinkDuration{0.2f},
		mBlinkColorOffest{255, 0, 0, 255}
	{
	}
	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
		UpdateBlink(deltaTime);
	}
	void Spaceship::SetVelocity(const sf::Vector2f& newVelocity)
	{
		mVelocity = newVelocity;
	}
	void Spaceship::Shoot()
	{
	}
	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
		mHealthComponent.onHealthChange.BindAction(GetWeakReference(), &Spaceship::OnHealthChange);
		mHealthComponent.onTakeDamage.BindAction(GetWeakReference(), &Spaceship::OnTakeDamage);
		mHealthComponent.onHealthEmpty.BindAction(GetWeakReference(), &Spaceship::Die);
	}
	void Spaceship::ApplyDamage(float amount)
	{
		mHealthComponent.ChangeHealth(-amount);
	}
	void Spaceship::Blink()
	{
		if (mBlinkTime == 0.f)
		{
			mBlinkTime = mBlinkDuration;
		}
	}
	void Spaceship::UpdateBlink(float deltaTime)
	{
		if (mBlinkTime > 0)
		{
			mBlinkTime -= deltaTime;
			mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0.f;

			GetSprite().setColor(LerpColor(sf::Color::White, mBlinkColorOffest, mBlinkTime));
		}
	}
	void Spaceship::OnHealthChange(float amount, float health, float maxHealth)
	{
		
	}
	void Spaceship::OnTakeDamage(float amount, float health, float maxHealth)
	{

		Blink();
	}
	void Spaceship::Die()
	{
		Explosion* explosion = new Explosion();
		explosion->SpawnExplosion(GetWorld(), GetActorLocation());
		DropReward();
		Destroy();
		delete explosion;
	}
	void Spaceship::DropReward()
	{
	}
}
