#pragma once
#include "box2d/b2_world.h"
#include "framework/Core.h"

namespace ly
{
	class Actor;
	class PhysicsContactListener : public b2ContactListener
	{
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	};
	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get();
		void Step(float deltaTime);
		b2Body* AddListener(Actor* listener);
		void RemoveListener(b2Body* listenerToRemove);
		float GetPhysicsScale() const { return mPhysicsScale; }

		static void CleanUp();

	protected:
		PhysicsSystem();

	private:
		void ProcessPendingRemoveListeners();
		static unique<PhysicsSystem> physicsSystem;
		b2World mPhysicsWorld;
		float mPhysicsScale;
		int mVelocityIteration;
		int mPostionIteration;
		PhysicsContactListener mContactListener;

		Set<b2Body*> mPendingRemoveListener;
	};
}