#include "Widgets/Widget.h"

namespace ly
{
	void Widget::NativeDraw(sf::RenderWindow& windowRef)
	{
		if (mIsVisible)
		{
			Draw(windowRef);
		}
	}
	bool Widget::HandleEvent(const sf::Event& event)
	{
		return false;
	}
	void Widget::SetWidgetLocation(const sf::Vector2f& newLocation)
	{
		mWidgetTransform.setPosition(newLocation);
		LocationUpdate(newLocation);
	}
	void Widget::SetWidgetRotation(float newRotation)
	{
		mWidgetTransform.setRotation(newRotation);
		RotationUpdate(newRotation);
	}
	void Widget::SetVisiblity(bool newVisibility)
	{
		mIsVisible = newVisibility;
	}
	
	sf::Vector2f Widget::GetCenterPosition() const
	{
		sf::FloatRect bound = GetBound();
		return sf::Vector2f{ bound.left + bound.width/2, bound.top + bound.height/2 };
	}
	
	Widget::Widget()
		:mIsVisible{true},
		mWidgetTransform{}
	{
	}
	void Widget::Draw(sf::RenderWindow& windowRef)
	{
	}
	void Widget::LocationUpdate(const sf::Vector2f& newLocation)
	{
	}
	void Widget::RotationUpdate(float newRotation)
	{
	}
}