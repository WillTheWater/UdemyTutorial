#include "framework/MathUtility.h"
#include "framework/World.h"
#include "VFX/Explosion.h"
#include "VFX/Particle.h"

namespace ly
{
	Explosion::Explosion(int particleAmount, float lifeTimeMin, float lifeTimeMax, float sizeMin, float sizeMax, float speedMin, float speedMax, const sf::Color& spawnParticleColor, const List<std::string>& particleImagePath)
		: mParticleAmount{ particleAmount },
		mLifeTimeMin{ lifeTimeMin },
		mLifeTimeMax{ lifeTimeMax },
		mSizeMin{ sizeMin },
		mSizeMax{ sizeMax },
		mSpeedMin{ speedMin },
		mSpeedMax{ speedMax },
		mSpawnParticleColor{ spawnParticleColor },
		mParticleImagePath{ particleImagePath }
	{
	}
	void Explosion::SpawnExplosion(World* world, const sf::Vector2f& location)
	{
		if (!world) { return; }

		for (int i = 0; i < mParticleAmount; ++i)
		{
			std::string particlePath = mParticleImagePath[(int)RandomRange(0, mParticleImagePath.size())];
			weak<Particle> newParticle = world->SpawnActor<Particle>(particlePath);
			newParticle.lock()->RandomLifeTime(mLifeTimeMin, mLifeTimeMax);
			newParticle.lock()->SetActorLocation(location);
			newParticle.lock()->RandomSize(mSizeMin, mSizeMax);
			newParticle.lock()->RandomVelocity(mSpeedMin, mSpeedMax);
			newParticle.lock()->GetSprite().setColor(mSpawnParticleColor);
		}
	}
}