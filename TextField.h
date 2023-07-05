#pragma once
#include <SFML/Graphics.hpp>
class TextField
{
public:
	bool focus;
	std::string placeholder;
	TextField(sf::Vector2f pos, sf::Vector2f size, std::string placeholder);
	sf::String value;
	sf::RectangleShape shape;
	void draw(sf::RenderWindow& window, sf::Font font);
	bool AABB(sf::Vector2i loc);
	void ontype(sf::String line);
};