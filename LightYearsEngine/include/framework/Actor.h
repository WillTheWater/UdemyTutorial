#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/Object.h"

class b2Body;

namespace ly
{
	class World;
	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		virtual ~Actor();
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		void SetTexture(const std::string& texturePath);
		void Render(sf::RenderWindow& window);

		void SetActorLocation(const sf::Vector2f& newLocation);
		void SetActorRotation(float newRotation);
		void AddActorLocationOffset(const sf::Vector2f& offsetLocation);
		void AddActorRotationOffset(float offsetRotation);
		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;
		sf::Vector2f GetActorForwardVector() const;
		sf::Vector2f GetActorRightVector() const;
		sf::FloatRect GetActorGlobalBounds() const;

		sf::Vector2u GetWindowSize() const;

		const World* GetWorld() const { return mOwningworld; }
		World* GetWorld() { return mOwningworld; }

		bool IsActorOutOfWindowBounds(float allowance = 10.f) const;
		
		void SetEnablePhysics(bool enable);
		virtual void OnActorBeginOverlap(Actor* other);
		virtual void OnActorEndOverlap(Actor* other);
		virtual void Destroy() override;
		static uint8 GetNeutralTeamID() { return mNeutralTeam; }

		void SetTeamID(uint8 teamID) { mTeamID = teamID; }

		uint8 GetTeamID()const { return mTeamID; }
		bool IsEnemy(Actor* other) const;

		virtual void ApplyDamage(float amout);

		const sf::Sprite& GetSprite() const { return mSprite; }
		sf::Sprite& GetSprite() { return mSprite; }


	private:
		void InitilizePhysics();
		void UninitilizePhysics();
		void UpdatePhysicsBodyTransform();
		void PivotOnOrigin();
		World* mOwningworld;
		bool mHasBeginPlay;

		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;
		b2Body* mPhysicsBody;
		bool mPhysicsEnabled;

		uint8 mTeamID;
		const static uint8 mNeutralTeam = 255;
	};
}