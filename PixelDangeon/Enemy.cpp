#include "Enemy.h"

Enemy::Enemy(int hp, int lim, int x_position, int y_position) : health(hp), ammo(lim / 2), limit_ammo(lim), x_pos(x_position), y_pos(y_position) {};

void Enemy::operator=(const Enemy& e)
{
	this->health = e.health;
	this->ammo = e.ammo;
	this->limit_ammo = e.limit_ammo;
	this->x_pos = e.x_pos;
	this->y_pos = e.y_pos;
}

void Enemy::SetHealth(const int& hp)
{
	this->health = hp;
}

int Enemy::GetHealth() const
{
	return health;
}

void Enemy::SetAmmo(const int& ammo)
{
	this->ammo = ammo;
}

int Enemy::GetAmmo() const
{
	return ammo;
}

void Enemy::SetLimitAmmo(const int& limit_ammo)
{
	this->limit_ammo = limit_ammo;
}

int Enemy::GetLimitAmmo() const
{
	return limit_ammo;
}

void Enemy::SetXPosition(const int& x)
{
	this->x_pos = x;
}

int Enemy::GetXPosition() const
{
	return x_pos;
}

void Enemy::SetYPosition(const int& y)
{
	this->y_pos = y;
}

int Enemy::GetYPosition() const
{
	return y_pos;
}

void Enemy::DrawBody(sf::RenderWindow& window) const
{
	sf::RectangleShape body;
	body.setFillColor(sf::Color::Color(101, 67, 33, 255));
	body.setSize(sf::Vector2f(20, 20));
	body.setPosition(x_pos - 10, y_pos - 10);
	window.draw(body);
	body.setFillColor(sf::Color::Green);
	body.setSize(sf::Vector2f(10, 10));
	body.setPosition(x_pos - 5, y_pos - 5);
	window.draw(body);
}

void Enemy::DrawCharacteristics(sf::RenderWindow& window) const
{
	sf::Text text1;
	sf::Font font;
	font.loadFromFile("bold.ttf");
	text1.setCharacterSize(25);
	text1.setFont(font);
	text1.setFillColor(sf::Color::Blue);
	text1.setStyle(sf::Text::Bold);
	text1.setString(std::to_string(health));
	text1.setPosition(window.getSize().y, 25);
	window.draw(text1);
}