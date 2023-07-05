#include <SFML/Graphics.hpp>
#include <mysqlx/xdevapi.h>
#include <iostream>
#include <vector>
#include "Button.h"
#include "TextField.h"
using namespace sf;
RenderWindow window(VideoMode(800, 600), L"DZ8", Style::Default);
std::vector<Button> delete_buttons;
TextField searchField(sf::Vector2f(10, 6), sf::Vector2f(200, 28), "condition");
Button searchButton(sf::Vector2f(215,5),sf::Vector2f(50,30),-1);
sf::Font font;
void drawDataTable(int x, int y, std::string condition) {
	delete_buttons.clear();
	try {

		mysqlx::SessionSettings sesssett("localhost", 33060, "user", "password", "database");
		mysqlx::Session session(sesssett);
		mysqlx::Schema schema = session.getDefaultSchema();
		mysqlx::Table table = schema.getTable("table");
		mysqlx::RowResult result;
		if (condition.empty()) {
			result = table.select("*").execute();
		}
		else {
			result = table.select("*").where(condition.c_str()).execute();
		}
		

		for (int i = 0; i < result.getColumnCount();i++) {
			auto& col = result.getColumn(i);
			std::string lab = col.getColumnLabel();
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(x + i * 150, y),sf::Color(0, 0, 0)),
				sf::Vertex(sf::Vector2f(x + i * 150, y + 20.f),sf::Color(0, 0, 0)),
				sf::Vertex(sf::Vector2f(x + i * 150, y),sf::Color(0, 0, 0)),
				sf::Vertex(sf::Vector2f(x + i * 150+150, y),sf::Color(0, 0, 0))
			};
			window.draw(line, 4, sf::Lines);
			sf::Text text;
			
				text.setFont(font);
				text.setString(lab);
				text.setCharacterSize(15);
				text.setFillColor(sf::Color(0,0,0));
				text.setPosition(x + i * 150+5, y);
				window.draw(text);
			
		}
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(x + result.getColumnCount() * 150, y),sf::Color(0, 0, 0)),
			sf::Vertex(sf::Vector2f(x + result.getColumnCount() * 150, y + 20.f),sf::Color(0, 0, 0))
		};
		window.draw(line, 4, sf::Lines);
		int j = 1;
		for (mysqlx::Row row : result.fetchAll()) {

			for (int i = 0; i < row.colCount(); i++) {
				std::stringstream ss;
				ss << row[i];
				std::string lab = ss.str();
				sf::Vertex line[] =
				{
					sf::Vertex(sf::Vector2f(x + i * 150, y + j * 20),sf::Color(0, 0, 0)),
					sf::Vertex(sf::Vector2f(x + i * 150, y + 20.f + j * 20),sf::Color(0, 0, 0)),
					sf::Vertex(sf::Vector2f(x + i * 150, y + j * 20),sf::Color(0, 0, 0)),
					sf::Vertex(sf::Vector2f(x + i * 150 + 150, y + j * 20),sf::Color(0, 0, 0))
				};
				window.draw(line, 4, sf::Lines);
				sf::Text text;
				sf::Font font;
				if (font.loadFromFile("Arial.ttf"))
				{
					text.setFont(font);
					text.setString(lab);
					text.setCharacterSize(15);
					text.setFillColor(sf::Color(0, 0, 0));
					text.setPosition(x + i * 150 + 5, y + j * 20);
					window.draw(text);
				}
				if (row[i].getType() == 2) {
					Button button(sf::Vector2f(x + i * 150 + 132.5f, y + j * 20 + 2.5f), sf::Vector2f(15.0f, 15.0f),row[i]);
					delete_buttons.push_back(button);
					button.draw(window);
				}
			}
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(x + result.getColumnCount() * 150, y + j * 20),sf::Color(0, 0, 0)),
				sf::Vertex(sf::Vector2f(x + result.getColumnCount() * 150, y + 20.f + j * 20),sf::Color(0, 0, 0))
			};
			window.draw(line, 4, sf::Lines);
			j++;
		}
		sf::Vertex lineEnd[] =
		{
			sf::Vertex(sf::Vector2f(x, y + j * 20),sf::Color(0, 0, 0)),
			sf::Vertex(sf::Vector2f(x + result.getColumnCount() * 150, y + j * 20),sf::Color(0, 0, 0))
		};
		window.draw(lineEnd, 4, sf::Lines);
		session.close();
	}
	catch (const mysqlx::Error& e) {
		std::cout << "Ошибка: " << e.what() << std::endl;
	}
}
void removeId(int id) {
	try {
		mysqlx::SessionSettings sesssett("localhost", 33060, "bulat5280", "Neznayka08", "DZ6");
		mysqlx::Session session(sesssett);
		std::stringstream sql;
		sql << "DELETE FROM classroom WHERE id=" << id;
		session.sql(sql.str()).execute();
		session.close();
	}
	catch (const mysqlx::Error& e) {
		std::cout << "Ошибка: " << e.what() << std::endl;
	}
}
int main()
{
	font.loadFromFile("Arial.ttf");
	window.clear(Color(200, 200, 200));
	drawDataTable(10,50,"");
	searchField.draw(window, font);
	searchButton.draw(window);
	window.display();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if (event.type == Event::MouseMoved) {
				for (Button button : delete_buttons) {
					if (button.AABB(sf::Mouse::getPosition(window))) {
						button.shape.setFillColor(sf::Color(255, 0, 0));
						button.draw(window);
						break;
					}
					else {
						button.shape.setFillColor(sf::Color(50, 50, 50));
						button.draw(window);
					}
				}
				if (searchField.AABB(sf::Mouse::getPosition(window))) {
					searchField.shape.setFillColor(sf::Color(230, 230, 230));
				}
				else {
					searchField.shape.setFillColor(sf::Color(255, 255, 255));
				}
				searchField.draw(window, font);
				if (searchButton.AABB(sf::Mouse::getPosition(window))) {
					searchButton.shape.setFillColor(sf::Color(200, 255, 200));
				}
				else {
					searchButton.shape.setFillColor(sf::Color(0, 255, 255));
				}
				searchButton.draw(window);
			}
			else if (event.type == Event::MouseButtonReleased) {
				for (Button button : delete_buttons) {
					if (button.AABB(sf::Mouse::getPosition(window))) {
						removeId(button.data);
						window.clear(Color(200, 200, 200));
						drawDataTable(10, 50, searchField.value);
						searchField.draw(window, font);
						searchButton.draw(window);
						window.display();
						break;
					}
				}
				if (searchField.AABB(sf::Mouse::getPosition(window))) {
					searchField.focus = true;
					searchField.shape.setOutlineColor(sf::Color(255, 0,0));
				}
				else {
					searchField.focus = false;
					searchField.shape.setOutlineColor(sf::Color(0,0,0));
				}
				searchField.draw(window, font);
				if (searchButton.AABB(sf::Mouse::getPosition(window))) {
					searchField.focus = false;
					searchField.shape.setOutlineColor(sf::Color(0, 0, 0));
					window.clear(Color(200, 200, 200));
					drawDataTable(10, 50, searchField.value);
					searchField.draw(window, font);
					searchButton.draw(window);
					window.display();
				}
				searchButton.draw(window);
			}
			else if (event.type == Event::TextEntered) {
				if (event.text.unicode == 8) {
					if (searchField.focus) {
						if (searchField.value.getSize() > 0) {
							searchField.value.erase(searchField.value.getSize() - 1, 1);
						}
					}
				}
				else {
					searchField.ontype(event.text.unicode);
				}
				searchField.draw(window,font);
			}
        }

        //window.clear(Color(200,200,200));
        window.display();
    }
    return 0;
}