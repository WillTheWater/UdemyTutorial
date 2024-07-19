#include <box2d/b2_body.h>
#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace ly
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		: mOwningworld{owningWorld},
		mHasBeginPlay{false},
		mSprite{},
		mTexture{},
		mPhysicsBody{nullptr},
		mPhysicsEnabled{false}
	{
		SetTexture(texturePath);
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
	}

	void Actor::Tick(float deltaTime)
	{
	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		mTexture = AssetManager::Get().LoadTecture(texturePath);
		if (!mTexture) return;

		mSprite.setTexture(*mTexture);

		int textureWidth = mTexture->getSize().x;
		int textureHieght = mTexture->getSize().y;
		mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHieght} });
		PivotOnOrigin();
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy())
			return;

		window.draw(mSprite);
	}

	void Actor::SetActorLocation(const sf::Vector2f& newLocation)
	{
		mSprite.setPosition(newLocation);
		UpdatePhysicsBodyTransform();
	}

	void Actor::SetActorRotation(float newRotation)
	{
		mSprite.setRotation(newRotation);
		UpdatePhysicsBodyTransform();

	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetLocation)
	{
		SetActorLocation(GetActorLocation() + offsetLocation);
	}

	void Actor::AddActorRotationOffset(float offsetRotation)
	{
		SetActorRotation(GetActorRotation() + offsetRotation);
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return mSprite.getPosition();
	}

	float Actor::GetActorRotation() const
	{
		return mSprite.getRotation();
	}

	sf::Vector2f Actor::GetActorForwardVector() const
	{
		return RotationToVector(GetActorRotation() - 90.f);
	}

	sf::Vector2f Actor::GetActorRightVector() const
	{
		return RotationToVector(GetActorRotation() + 90.f);
	}

	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return mSprite.getGlobalBounds();
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return mOwningworld->GetWindowSize();
	}

	bool Actor::IsActorOutOfWindowBounds() const
	{
		float windowWidth = GetWorld()->GetWindowSize().x;
		float windowHeight = GetWorld()->GetWindowSize().y;

		float actorWidth = GetActorGlobalBounds().width;
		float actorHeight = GetActorGlobalBounds().height;

		sf::Vector2f actorPosition = GetActorLocation();

		if (actorPosition.x < -actorWidth)
		{
			return true;
		}
		if (actorPosition.x > windowWidth + actorWidth)
		{
			return true;
		}
		if (actorPosition.y < -actorHeight)
		{
			return true;
		}
		if (actorPosition.y > windowHeight + actorHeight)
		{
			return true;
		}
		return false;
	}

	void Actor::SetEnablePhysics(bool enable)
	{
		mPhysicsEnabled = enable;
		if (mPhysicsEnabled)
		{
			InitilizePhysics();
		}
		else 
		{
			UninitilizePhysics();
		}
			
	}

	void Actor::OnActorBeginOverlap(Actor* other)
	{
		LOG("Begin Overlap", "\n");
	}

	void Actor::OnActorEndOverlap(Actor* other)
	{
		LOG("End Overlap", "\n");
	}

	void Actor::Destroy()
	{
		UninitilizePhysics();
		Object::Destroy();
	}

	void Actor::InitilizePhysics()
	{
		if(!mPhysicsBody)
		{
			mPhysicsBody = PhysicsSystem::Get().AddListener(this);
		}
	}

	void Actor::UninitilizePhysics()
	{
		if (mPhysicsBody)
		{
			PhysicsSystem::Get().RemoveListener(mPhysicsBody);
			mPhysicsBody = nullptr;
		}
	}

	void Actor::UpdatePhysicsBodyTransform()
	{
		if (mPhysicsBody)
		{
			float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			b2Vec2 position{ GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale };
			float rotation = DegreesToRadians(GetActorRotation());
			mPhysicsBody->SetTransform(position, rotation);
		}
	}

	void Actor::PivotOnOrigin()
	{
		sf::FloatRect bound = mSprite.getLocalBounds();
		mSprite.setOrigin(bound.width / 2, bound.height / 2);
	}

}