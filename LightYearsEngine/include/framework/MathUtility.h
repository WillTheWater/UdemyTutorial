#pragma once
#include "SFML/Graphics.hpp"

namespace ly
{
	sf::Vector2f RotationToVector(float rotation);
	float DegreesToRadians(float degrees);
	float RadiansToDegrees(float radians);

	template<typename T>
	float GetVectorLength(const sf::Vector2<T>& vector)
	{
		return std::sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	template<typename T>
	sf::Vector2<T>& ScaleVector(sf::Vector2<T>& vectorToScale, float amount)
	{
		vectorToScale.x *= amount;
		vectorToScale.y *= amount;
		return vectorToScale;
	}

	template<typename T>
	sf::Vector2<T>& Normalize(sf::Vector2<T>& vector)
	{
		float vectorLenght = GetVectorLength<T>(vector);
		if (vectorLenght == 0.f) return sf::Vector2<T>{};

		ScaleVector(vector, 1.f/vectorLenght);
		return vector;
	}
}