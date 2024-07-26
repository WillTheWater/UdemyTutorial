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
		LocationUdate(newLocation);
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
	Widget::Widget()
		:mIsVisible{true},
		mWidgetTransform{}
	{
	}
	void Widget::Draw(sf::RenderWindow& windowRef)
	{
	}
	void Widget::LocationUdate(const sf::Vector2f& newLocation)
	{
	}
	void Widget::RotationUpdate(float newRotation)
	{
	}
}