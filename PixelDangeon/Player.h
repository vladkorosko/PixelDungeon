#pragma once
#include "Enemy.h"

class Player: public Enemy
{
public:
	Player(int hp, int lim, int x_position, int y_position) : Enemy(hp, lim, x_position, y_position) {}

	void DrawBody(sf::RenderWindow& window) const
	{
		sf::RectangleShape body;
		body.setFillColor(sf::Color::Green);
		body.setSize(sf::Vector2f(20, 20));
		body.setPosition(x_pos - 10, y_pos - 10);
		window.draw(body);
		body.setFillColor(sf::Color::Color(101, 67, 33, 255));
		body.setSize(sf::Vector2f(10, 10));
		body.setPosition(x_pos - 5, y_pos - 5);
		window.draw(body);
	}

	void DrawCharacteristics(sf::RenderWindow& window) const
	{
		sf::Text text1;
		sf::Font font;
		font.loadFromFile("bold.ttf");
		text1.setCharacterSize(25);
		text1.setFont(font);
		text1.setFillColor(sf::Color::Blue);
		text1.setStyle(sf::Text::Bold);
		text1.setString(to_string(health));
		text1.setPosition(window.getSize().y, 25);
		window.draw(text1);

		text1.setFillColor(sf::Color::Red);
		text1.setString(to_string(ammo) + " (max: " + to_string(limit_ammo) + ")");
		text1.setPosition(window.getSize().y, 50);
		window.draw(text1);
	}
};