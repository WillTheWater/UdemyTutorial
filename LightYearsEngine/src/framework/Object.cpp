#include "Framework/Object.h"

namespace ly
{
	
	unsigned int Object::mUniqueIDCounter = 0;

	Object::Object()
		:mIsPendingDestroy{false},
		mUniqueID{GetNextID()}
	{
	}

	Object::~Object()
	{
		LOG("Object Destroyed", "\n");
	}

	void Object::Destroy()
	{
		onDestroy.Broadcast(this);
		mIsPendingDestroy = true;
	}

	weak<Object> Object::GetWeakReference()
	{
		return weak_from_this();
	}

	weak<const Object> Object::GetWeakReference() const
	{
		return weak_from_this();
	}

	unsigned int Object::GetNextID()
	{
		return mUniqueIDCounter++;
	}
	
}

