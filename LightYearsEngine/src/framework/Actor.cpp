#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		: mOwningworld{owningWorld},
		mHasBeginPlay{false},
		mSprite{},
		mTexture{}
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

	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy())
		{
			Tick(deltaTime);
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

	void Actor::SetTexture(const std::string& texturePath)
	{
		mTexture.loadFromFile(texturePath);
		mSprite.setTexture(mTexture);
		int textureWidth = mTexture.getSize().x;
		int textureHieght = mTexture.getSize().y;
		mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHieght} });
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy())
			return;

		window.draw(mSprite);
	}

}