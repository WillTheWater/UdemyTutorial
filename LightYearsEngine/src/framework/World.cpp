#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"

namespace ly
{
	World::World(Application* owingApp)
		: mOwningApp{ owingApp },
		mBeginPlay{false},
		mActors{},
		mPendingActors{}
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
		for (shared<Actor> actor : mPendingActors)
		{
			mActors.push_back(actor);
			actor->BeginPlayInternal();
		}

		mPendingActors.clear();

		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			if (iter->get()->IsPendingDestroy())
			{
				iter = mActors.erase(iter);
			}
			else
			{
				iter->get()->TickInternal(deltaTime);
				++iter;
			}
		}

		Tick(deltaTime);
	}
	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : mActors)
		{
			actor->Render(window);
		}
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