#pragma once
#include "Enemy.h"

class Player: public Enemy
{
private:
	int ammo;
	int limit_ammo;

public:
	Player(int hp, int lim, int x_position, int y_position): Enemy(hp, x_position, y_position)
	{
		ammo = 10;
		limit_ammo = lim;
	}

	void operator=(const Player& p)
	{
		this->health = p.health;
		this->ammo = p.ammo;
		this->limit_ammo = p.limit_ammo;
		this->x_pos = p.x_pos;
		this->y_pos = p.y_pos;
	}

	void SetAmmo(const int& ammo)
	{
		this->ammo = ammo;
	}

	int GetAmmo() const
	{
		return ammo;
	}

	void SetLimitAmmo(const int& limit_ammo)
	{
		this->limit_ammo = limit_ammo;
	}

	int GetLimitAmmo() const
	{
		return limit_ammo;
	}

	void DrawBody(sf::RenderWindow& window)
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

	void DrawCharacteristics(sf::RenderWindow& window)
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