#pragma once
#include "SFML/Graphics.hpp"
#include "framework/Object.h"

namespace ly
{
	class Widget : public Object
	{
	public:
		void NativeDraw(sf::RenderWindow& windowRef);
		virtual bool HandleEvent(const sf::Event& event);
		void SetWidgetLocation(const sf::Vector2f& newLocation);
		void SetWidgetRotation(float newRotation);
		sf::Vector2f GetWidgetLocation() const { return mWidgetTransform.getPosition(); }
		float GetWidgetRotation() const { return mWidgetTransform.getRotation(); }

		void SetVisiblity(bool newVisibility);
		bool GetVisibility() const { return mIsVisible; }
		virtual sf::FloatRect GetBound() const = 0;
		sf::Vector2f GetCenterPosition() const;

	protected:
		Widget();

	private:
		virtual void Draw(sf::RenderWindow& windowRef);
		virtual void LocationUpdate(const sf::Vector2f& newLocation);
		virtual void RotationUpdate(float newRotation);
		sf::Transformable mWidgetTransform;
		bool mIsVisible;
	};
}