#include "widgets/GameplayHUD.h"

namespace ly
{
	GameplayHUD::GameplayHUD()
		: mFrameRateText{"Framerate: "}
	{
		mFrameRateText.SetFontSize(60);
	}
	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mFrameRateText.NativeDraw(windowRef);
	}
	void GameplayHUD::Tick(float deltaTime)
	{
		int framerate = int(1/deltaTime);
		std::string framerateText = "Framerate: " + std::to_string(framerate);
		mFrameRateText.SetString(framerateText);
	}
}