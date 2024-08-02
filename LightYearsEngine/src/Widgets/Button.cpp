#include "framework/AssetManager.h"
#include "Widgets/Button.h"

namespace ly
{
	Button::Button(const std::string& textString, const std::string& buttonTexturePath)
		: mButtonTexture{AssetManager::Get().LoadTexture(buttonTexturePath)},
		mButtonSprite{*mButtonTexture.get()},
		mButtonFont{AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf")},
		mButtonText{textString, *mButtonFont.get()},
		mButtonDefualtColor{128, 128, 128, 255},
		mButtonDownColor{64, 64, 64, 255},
		mButtonHoverColor{158, 158, 158, 255},
		IsButtonDown{false}
	{
		mButtonSprite.setColor(mButtonDefualtColor);
		CenterText();
	}
	sf::FloatRect Button::GetBound() const
	{
		return mButtonSprite.getGlobalBounds();
	}
	void Button::SetTextString(const std::string& newString)
	{ 
		mButtonText.setString(newString);
		CenterText();
	}
	void Button::SetButtonFontSize(unsigned int fontSize)
	{
		mButtonText.setCharacterSize(fontSize);
		CenterText();
	}
	bool Button::HandleEvent(const sf::Event& windowEvent)
	{
		bool handled = false;
		if (windowEvent.type == sf::Event::MouseButtonReleased)
		{
			if (windowEvent.mouseButton.button == sf::Mouse::Left)
			{
				if (mButtonSprite.getGlobalBounds().contains(windowEvent.mouseButton.x, windowEvent.mouseButton.y) && IsButtonDown)
				{
					onButtonClicked.Broadcast();
					handled = true;
				}
			}
			OnButtonUp();
		}
		else if (windowEvent.type == sf::Event::MouseButtonPressed)
		{
			if (mButtonSprite.getGlobalBounds().contains(windowEvent.mouseButton.x, windowEvent.mouseButton.y))
			{
				OnButtonDown();
				handled = true;
			}
		}
		else if (windowEvent.type == sf::Event::MouseMoved)
		{
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (mButtonSprite.getGlobalBounds().contains(windowEvent.mouseMove.x, windowEvent.mouseMove.y))
				{
					OnButtonHover();
				}
				else
				{
					OnButtonUp();
				}
					handled = true;
			}
		}
		return handled || Widget::HandleEvent(windowEvent);
	}
	void Button::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mButtonSprite);
		windowRef.draw(mButtonText);
		CenterText();
	}
	void Button::LocationUpdate(const sf::Vector2f& location)
	{
		mButtonSprite.setPosition(location);
		mButtonText.setPosition(location);
	}
	void Button::RotationUpdate(float rotation)
	{
		mButtonSprite.setRotation(rotation);
		mButtonText.setRotation(rotation);
	}
	void Button::CenterText()
	{
		sf::Vector2f center = GetCenterPosition();
		sf::FloatRect textBound = mButtonText.getGlobalBounds();
		mButtonText.setPosition(center - sf::Vector2f{ textBound.width / 2, textBound.height });
	}
	void Button::OnButtonUp()
	{
		IsButtonDown = false;
		mButtonSprite.setColor(mButtonDefualtColor);
	}
	void Button::OnButtonDown()
	{
		IsButtonDown = true;
		mButtonSprite.setColor(mButtonDownColor);
	}
	void Button::OnButtonHover()
	{
		mButtonSprite.setColor(mButtonHoverColor);
	}
}