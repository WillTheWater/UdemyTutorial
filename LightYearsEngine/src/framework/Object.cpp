#include "Framework/Object.h"
#include "framework/Core.h"

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
		mIsPendingDestroy = true;
	}
	
}

