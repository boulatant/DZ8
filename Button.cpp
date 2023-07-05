#include "Button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f size, uint64_t data)
{
	this->shape = sf::RectangleShape(size);
	this->shape.setPosition(pos);
	this->shape.setFillColor(sf::Color(50, 50, 50));
	this->data = data;
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(this->shape);
}

bool Button::AABB(sf::Vector2i loc) {
	return loc.x >= shape.getPosition().x && loc.x <= shape.getPosition().x + shape.getSize().x &&
		loc.y >= shape.getPosition().y && loc.y <= shape.getPosition().y + shape.getSize().y;
}

void Button::onclick() {

}
