#include "Widgets/TextWidget.h"
#include "framework/AssetManager.h"


namespace ly
{
	TextWidget::TextWidget(const std::string& textString, const std::string& fontPath, unsigned int fontSize)
		: mFont{AssetManager::Get().LoadFont(fontPath)},
		mText{textString, *(mFont.get()), fontSize}
	{
	}
	void TextWidget::SetString(const std::string& newString)
	{
		mText.setString(newString);
	}
	void TextWidget::SetFontSize(unsigned int newSize)
	{
		mText.setCharacterSize(newSize);
	}
	void TextWidget::LocationUdate(const sf::Vector2f& newLocation)
	{
		mText.setPosition(newLocation);
	}
	void TextWidget::RotationUpdate(float newRotation)
	{
		mText.setRotation(newRotation);
	}
	void TextWidget::Draw(sf::RenderWindow windowRef)
	{
		windowRef.draw(mText);
	}
}