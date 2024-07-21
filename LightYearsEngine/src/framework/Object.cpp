#include "Framework/Object.h"

namespace ly
{
	


	Object::Object()
		:mIsPendingDestroy{false}
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
	
}

