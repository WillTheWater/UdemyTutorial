#pragma once
#include "Widgets/Widget.h"

namespace ly
{
	class ValueGauge : public Widget
	{
	public:
		ValueGauge(const sf::Vector2f& size = sf::Vector2f{300.f, 40.f}, float initialPercent = 0.75f,
			const sf::Color& foregroundColor = sf::Color{128, 255, 128, 255},
			const sf::Color backgroundColor = sf::Color{ 128, 128, 128, 255 });

		void UpdateValue(float value, float maxValue);
		virtual sf::FloatRect GetBound() const override;

		void SetTextSize(unsigned int textSize);

		void SetForegroundColor(const sf::Color& color);
		void SetBackgroundColor(const sf::Color& color);

	private:
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void LocationUpdate(const sf::Vector2f& newLocation) override;
		virtual void RotationUpdate(float newRotation) override;
		void CenterText();
		shared<sf::Font> mFont;
		sf::Text mText;

		sf::RectangleShape mBarFront;
		sf::RectangleShape mBarBack;

		sf::Color mForegroundColor;
		sf::Color mBackgroundColor;

		float mPercent;
	};
}