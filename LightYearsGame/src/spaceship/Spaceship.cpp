#include "spaceship/Spaceship.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{ owningWorld, texturePath },
		mVelocity{},
		mHealthComponent{100.f, 100.f}
	{
	}
	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
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
		mHealthComponent.onHalthChange.BindAction(GetWeakReference(), &Spaceship::OnHealthChange);

		mHealthComponent.onHalthChange.Broadcast(10.f, 90.f, 100.f);
	}
	void Spaceship::OnHealthChange(float amount, float health, float maxHealth)
	{
		LOG("Health changed!", "\n");
	}
}
