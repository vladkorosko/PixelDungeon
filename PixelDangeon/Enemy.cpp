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
	if(ammo>limit_ammo)
		this->ammo = limit_ammo;
	else
		this->ammo = ammo;
}

int Enemy::GetAmmo() const
{
	return ammo;
}

void Enemy::SetLimitAmmo(const int& limit_ammo)
{
	this->limit_ammo = limit_ammo;
	if (limit_ammo < ammo)
		this->ammo = limit_ammo;
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

TEST_CASE("testing enemy constructor with getters")
{
	{	
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120;
		Enemy e(hp, lim_ammo, x_pos, y_pos);
		CHECK(hp == e.GetHealth());
		CHECK(lim_ammo == e.GetLimitAmmo());
		CHECK(ammo == e.GetAmmo());
		CHECK(x_pos == e.GetXPosition());
		CHECK(y_pos == e.GetYPosition());
	}

	{
		int hp = 10, lim_ammo = 5, ammo = lim_ammo / 2, x_pos = 55, y_pos = 60;
		Enemy e(hp, lim_ammo, x_pos, y_pos);
		CHECK(hp == e.GetHealth());
		CHECK(lim_ammo == e.GetLimitAmmo());
		CHECK(ammo == e.GetAmmo());
		CHECK(x_pos == e.GetXPosition());
		CHECK(y_pos == e.GetYPosition());
	}
}

TEST_CASE("testing operator=")
{
	{
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120;
		Enemy e1(hp, lim_ammo, x_pos, y_pos);
		Enemy e_copy = e1;
		CHECK(hp == e_copy.GetHealth());
		CHECK(lim_ammo == e_copy.GetLimitAmmo());
		CHECK(ammo == e_copy.GetAmmo());
		CHECK(x_pos == e_copy.GetXPosition());
		CHECK(y_pos == e_copy.GetYPosition());
	}

	{
		int hp = 10, lim_ammo = 5, ammo = lim_ammo / 2, x_pos = 55, y_pos = 60;
		Enemy e1(hp, lim_ammo, x_pos, y_pos);
		Enemy e_copy = e1;
		CHECK(hp == e_copy.GetHealth());
		CHECK(lim_ammo == e_copy.GetLimitAmmo());
		CHECK(ammo == e_copy.GetAmmo());
		CHECK(x_pos == e_copy.GetXPosition());
		CHECK(y_pos == e_copy.GetYPosition());
	}
}

TEST_CASE("testing setters")
{
	{	
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120;
		Enemy e(hp, lim_ammo, x_pos, y_pos);
		int new_hp = 50;
		e.SetHealth(new_hp);
		CHECK(new_hp == e.GetHealth());
		CHECK(lim_ammo == e.GetLimitAmmo());
		CHECK(ammo == e.GetAmmo());
		CHECK(x_pos == e.GetXPosition());
		CHECK(y_pos == e.GetYPosition());
	}
	{
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120;
		Enemy e(hp, lim_ammo, x_pos, y_pos);
		int new_hp = 200;
		e.SetHealth(new_hp);
		CHECK(new_hp == e.GetHealth());
		CHECK(lim_ammo == e.GetLimitAmmo());
		CHECK(ammo == e.GetAmmo());
		CHECK(x_pos == e.GetXPosition());
		CHECK(y_pos == e.GetYPosition());
	}

	{
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120;
		Enemy e(hp, lim_ammo, x_pos, y_pos);
		int new_ammo = 200;
		e.SetAmmo(new_ammo);
		CHECK(hp == e.GetHealth());
		CHECK(lim_ammo == e.GetLimitAmmo());
		if (new_ammo > lim_ammo)
			CHECK(lim_ammo == e.GetAmmo());
		else
			CHECK(new_ammo == e.GetAmmo());
		CHECK(x_pos == e.GetXPosition());
		CHECK(y_pos == e.GetYPosition());
	}

	{
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120;
		Enemy e(hp, lim_ammo, x_pos, y_pos);
		int new_ammo = 2;
		e.SetAmmo(new_ammo);
		CHECK(hp == e.GetHealth());
		CHECK(lim_ammo == e.GetLimitAmmo());
		if (new_ammo > lim_ammo)
			CHECK(lim_ammo == e.GetAmmo());
		else
			CHECK(new_ammo == e.GetAmmo());
		CHECK(x_pos == e.GetXPosition());
		CHECK(y_pos == e.GetYPosition());
	}

	{
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120;
		Enemy e(hp, lim_ammo, x_pos, y_pos);
		int new_limit = 200;
		e.SetLimitAmmo(new_limit);
		CHECK(hp == e.GetHealth());
		CHECK(new_limit == e.GetLimitAmmo());
		if (ammo > new_limit)
			CHECK(new_limit == e.GetAmmo());
		else
			CHECK(ammo == e.GetAmmo());
		CHECK(x_pos == e.GetXPosition());
		CHECK(y_pos == e.GetYPosition());
	}

	{
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120;
		Enemy e(hp, lim_ammo, x_pos, y_pos);
		int new_limit = 2;
		e.SetLimitAmmo(new_limit);
		CHECK(hp == e.GetHealth());
		CHECK(new_limit == e.GetLimitAmmo());
		if (ammo > new_limit)
			CHECK(new_limit == e.GetAmmo());
		else
			CHECK(ammo == e.GetAmmo());
		CHECK(x_pos == e.GetXPosition());
		CHECK(y_pos == e.GetYPosition());
	}

	{
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120;
		Enemy e(hp, lim_ammo, x_pos, y_pos);
		int new_x = 50;
		e.SetXPosition(new_x);
		CHECK(hp == e.GetHealth());
		CHECK(lim_ammo == e.GetLimitAmmo());
		CHECK(ammo == e.GetAmmo());
		CHECK(new_x == e.GetXPosition());
		CHECK(y_pos == e.GetYPosition());
	}
	{
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120;
		Enemy e(hp, lim_ammo, x_pos, y_pos);
		int new_x = 170;
		e.SetXPosition(new_x);
		CHECK(hp == e.GetHealth());
		CHECK(lim_ammo == e.GetLimitAmmo());
		CHECK(ammo == e.GetAmmo());
		CHECK(new_x == e.GetXPosition());
		CHECK(y_pos == e.GetYPosition());
	}

	{
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120;
		Enemy e(hp, lim_ammo, x_pos, y_pos);
		int new_y = 50;
		e.SetYPosition(new_y);
		CHECK(hp == e.GetHealth());
		CHECK(lim_ammo == e.GetLimitAmmo());
		CHECK(ammo == e.GetAmmo());
		CHECK(x_pos == e.GetXPosition());
		CHECK(new_y == e.GetYPosition());
	}

	{
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120;
		Enemy e(hp, lim_ammo, x_pos, y_pos);
		int new_y = 150;
		e.SetYPosition(new_y);
		CHECK(hp == e.GetHealth());
		CHECK(lim_ammo == e.GetLimitAmmo());
		CHECK(ammo == e.GetAmmo());
		CHECK(x_pos == e.GetXPosition());
		CHECK(new_y == e.GetYPosition());
	}
}