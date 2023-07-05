#include "TextField.h"
#include <SFML/Graphics.hpp>
TextField::TextField(sf::Vector2f pos, sf::Vector2f size, std::string placeholder)
{
	this->shape = sf::RectangleShape(size);
	this->shape.setPosition(pos);
	this->shape.setFillColor(sf::Color(255, 255, 255));
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setOutlineThickness(1);
	this->value = "";
	this->focus = false;
	this->placeholder = placeholder;
}
void TextField::draw(sf::RenderWindow& window, sf::Font font) {
	sf::Text text(value, font, shape.getSize().y-10);
	text.setPosition(shape.getPosition()+sf::Vector2f(5,2));
	if (!focus&&value.isEmpty()) {
		text.setFillColor(sf::Color(100, 100, 100));
		text.setString(placeholder);
	}
	else {
		text.setFillColor(sf::Color(0, 0, 0));
	}
	window.draw(shape);
	window.draw(text);
}

void TextField::ontype(sf::String line) {
	if (focus) {
		value += line;
	}
}

bool TextField::AABB(sf::Vector2i loc) {
	return loc.x >= shape.getPosition().x && loc.x <= shape.getPosition().x + shape.getSize().x &&
		loc.y >= shape.getPosition().y && loc.y <= shape.getPosition().y + shape.getSize().y;
}