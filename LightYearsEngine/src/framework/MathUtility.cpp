#include "framework/MathUtility.h"

namespace ly
{
	const float pi = 3.1415926535;

	sf::Vector2f RotationToVector(float rotation)
	{
		float radians = DegreesToRadians(rotation);
		return sf::Vector2f(std::cos(radians), std::sin(radians));
	}
	float DegreesToRadians(float degrees)
	{
		return degrees * (pi/180.f);
	}
	float RadiansToDegrees(float radians)
	{
		return radians * (180.f/pi);
	}
}
