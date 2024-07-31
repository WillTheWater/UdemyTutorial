#pragma once
#include "SFML/Graphics.hpp"
#include "framework/Core.h"
#include "Widgets/Widget.h"


namespace ly
{
	class TextWidget : public Widget
	{
	public:
		TextWidget(const std::string& textString, 
			const std::string& fontPath = "SpaceShooterRedux/Bonus/kenvector_future.ttf",
			unsigned int fontSize = 100
			);

		void SetString(const std::string& newString);
		void SetFontSize(unsigned int newSize);
		virtual sf::FloatRect GetBound() const override;

	private:
		virtual void LocationUpdate(const sf::Vector2f& newLocation) override;
		virtual void RotationUpdate(float newRotation) override;
		virtual void Draw(sf::RenderWindow windowRef);
		shared<sf::Font> mFont;
		sf::Text mText;

	};
}