#include "framework/World.h"
#include "framework/Core.h"

namespace ly
{
	World::World(Application* owingApp)
		: mOwningApp{ owingApp },
		mBeginPlay{false}
	{

	}
	void World::BeginPlayInternal()
	{
		if (!mBeginPlay)
		{
			mBeginPlay = true;
			BeginPlay();
		}
	}
	void World::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
	}
	World::~World()
	{
	}
	void World::BeginPlay()
	{
		LOG("BeginPlay", "\n");
	}
	void World::Tick(float deltaTime)
	{
		LOG("Framerate: %f", 1.f/deltaTime);
	}
}