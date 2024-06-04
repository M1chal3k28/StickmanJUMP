#pragma once

#include <SFML\Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);
	virtual ~Collider();

	bool checkCollision(Collider other);

private:
	sf::RectangleShape& body;
};

