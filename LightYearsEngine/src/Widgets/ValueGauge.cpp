#include "Widgets/ValueGauge.h"
#include "framework/AssetManager.h"


namespace ly
{
	ValueGauge::ValueGauge(const sf::Vector2f& size, float initialPercent, const sf::Color& foregroundColor, const sf::Color backgroundColor)
		: mFont{ AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf") },
		mText{ "", *mFont.get() },
		mBarFront{ size },
		mBarBack{ size },
		mPercent{ initialPercent },
		mForegroundColor{foregroundColor},
		mBackgroundColor{backgroundColor}
	{
		mBarFront.setFillColor(mForegroundColor);
		mBarBack.setFillColor(mBackgroundColor);
		SetTextSize(30);
	}
	void ValueGauge::UpdateValue(float value, float maxValue)
	{
		if (maxValue == 0) { return; }
		mPercent = value / maxValue;
		std::string displayValue = std::to_string((int)value) + "/" + std::to_string((int)maxValue);
		mText.setString(displayValue);

		sf::Vector2f barSize = mBarBack.getSize();
		mBarFront.setSize({barSize.x * mPercent, barSize.y });
		CenterText();
	}
	sf::FloatRect ValueGauge::GetBound() const
	{
		return mBarBack.getGlobalBounds();
	}

	void ValueGauge::SetTextSize(unsigned int textSize)
	{
		mText.setCharacterSize(textSize);
	}

	void ValueGauge::SetForegroundColor(const sf::Color& color)
	{
		mBarFront.setFillColor(color);
	}

	void ValueGauge::SetBackgroundColor(const sf::Color& color)
	{
		mBarBack.setFillColor(color);

	}
	
	void ValueGauge::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mBarBack);
		windowRef.draw(mBarFront);
		windowRef.draw(mText);
		CenterText();
	}
	void ValueGauge::LocationUpdate(const sf::Vector2f& newLocation)
	{
		mBarBack.setPosition(newLocation);
		mBarFront.setPosition(newLocation);
	}
	void ValueGauge::RotationUpdate(float newRotation)
	{
		mText.setRotation(newRotation);
		mBarBack.setRotation(newRotation);
		mBarFront.setRotation(newRotation);
	}
	void ValueGauge::CenterText()
	{
		sf::Vector2f center = GetCenterPosition();
		sf::FloatRect textBound = mText.getGlobalBounds();
		mText.setPosition(center - sf::Vector2f{textBound.width/2, textBound.height});

	}
}