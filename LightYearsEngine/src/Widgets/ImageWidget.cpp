#include "Widgets/ImageWidget.h"
#include "framework/AssetManager.h"


namespace ly
{
	ImageWidget::ImageWidget(const std::string imagePath)
		: mTexture{AssetManager::Get().LoadTexture(imagePath)},
		mSprite{*mTexture.get()}
	{
	}
	void ImageWidget::SetImage(const shared<sf::Texture>& newTexture)
	{
		if (newTexture)
		{
			mTexture = newTexture;
			mSprite.setTexture(*mTexture.get());
		}
	}
	sf::FloatRect ImageWidget::GetBound() const
	{
		return mSprite.getGlobalBounds();
	}
	void ImageWidget::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mSprite);
	}
	void ImageWidget::LocationUpdate(const sf::Vector2f& newLocation)
	{
		mSprite.setPosition(newLocation);
	}
	void ImageWidget::RotationUpdate(float newRotation)
	{
		mSprite.setRotation(newRotation);
	}
}