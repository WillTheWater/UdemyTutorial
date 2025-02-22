#include "gameplay/HealthComponent.h"
#include "framework/Core.h"

namespace ly
{
	HealthComponent::HealthComponent(float health, float maxHealth)
		: mHealth{health},
		mMaxHealth{maxHealth}
	{
	}
	void HealthComponent::ChangeHealth(float amount)
	{
		if (amount == 0) return;
		if (mHealth == 0) return;

		mHealth += amount;
		if (mHealth < 0)
		{
			mHealth = 0;
		}

		if (mHealth > mMaxHealth)
		{
			mHealth = mMaxHealth;
		}

		onHealthChange.Broadcast(amount, mHealth, mMaxHealth);

		if (amount < 0)
		{
			TakenDamage(-amount);
			if (mHealth <= 0)
			{
				HealthEmpty();
			}
		}


	}
	void HealthComponent::TakenDamage(float amount)
	{
		onTakeDamage.Broadcast(amount, mHealth, mMaxHealth);
	}
	void HealthComponent::HealthEmpty()
	{
		onHealthEmpty.Broadcast();
	}

}