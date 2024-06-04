#include "Ground.h"
#include <iostream>

// Functions
void Ground::initRec()
{
	this->groundRec.setSize(sf::Vector2f(1000.f, 114.f));
	this->groundRec.setFillColor(sf::Color(255, 255, 255));
	this->groundRec.setPosition(sf::Vector2f(0.f, 490.f));
}

// Constructor
Ground::Ground()
{
	this->initRec();
}
