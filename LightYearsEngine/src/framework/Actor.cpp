#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{



	Actor::Actor(World* owningWorld)
		: mOwningworld{owningWorld},
		mHasBeginPlay{false}
	{

	}

	Actor::~Actor()
	{
		LOG("Actor Destroyed", "\n");
	}

	void Actor::BeginPlayInternal()
	{
		if (!mHasBeginPlay)
		{
			mHasBeginPlay = true;
			BeginPlay();
		}
	}

	void Actor::BeginPlay()
	{
		LOG("ActorBegin Play", "\n");
	}

	void Actor::Tick(float deltaTime)
	{
		LOG("Actor Tick", "\n");
	}

}