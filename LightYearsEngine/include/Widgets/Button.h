#pragma once
#include "Widgets/Widget.h"
#include "framework/Delegate.h"

namespace ly
{
	class Button : public Widget
	{
	public:
		Button(const std::string& textString = "Button",
			const std::string& buttongTexturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png");
		virtual sf::FloatRect GetBound() const;
		void SetTextString(const std::string& newString);
		void SetButtonFontSize(unsigned int fontSize);
		virtual bool HandleEvent(const sf::Event& windowEvent) override;
		Delegate<> onButtonClicked;

	private:
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void LocationUpdate(const sf::Vector2f& location);
		virtual void RotationUpdate(float rotation);
		void CenterText();

		shared<sf::Texture> mButtonTexture;
		sf::Sprite mButtonSprite;
		shared<sf::Font> mButtonFont;
		sf::Text mButtonText;
		sf::Color mButtonDefualtColor;
		sf::Color mButtonDownColor;
		sf::Color mButtonHoverColor;

		bool IsButtonDown;
		void OnButtonUp();
		void OnButtonDown();
		void OnButtonHover();
	};
}