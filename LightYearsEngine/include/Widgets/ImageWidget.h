#pragma once
#include "SFML/Graphics.hpp"
#include "Widgets/Widget.h"

namespace ly
{
	class ImageWidget : public Widget
	{
	public:
		ImageWidget(const std::string imagePath);
		void SetImage(const shared<sf::Texture>& newTexture);
		virtual sf::FloatRect GetBound() const override;
	private:
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void LocationUpdate(const sf::Vector2f& newLocation) override;
		virtual void RotationUpdate(float newRotation) override;
		shared<sf::Texture> mTexture;
		sf::Sprite mSprite;
	};
}