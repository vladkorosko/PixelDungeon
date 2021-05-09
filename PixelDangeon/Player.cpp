#include "Player.h"

Player::Player(int hp, int lim, int x_position, int y_position) : Enemy(hp, lim, x_position, y_position) { int score = 0; }

void Player::SetScore(int sc)
{
	this->score = sc;
}

int Player::GetScore() const
{
	return score;
}

void Player::DrawBody(sf::RenderWindow& window) const
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

void Player::DrawCharacteristics(sf::RenderWindow& window) const
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

	text1.setFillColor(sf::Color::Red);
	text1.setString(std::to_string(ammo) + " (max: " + std::to_string(limit_ammo) + ")");
	text1.setPosition(window.getSize().y, 50);
	window.draw(text1);

	text1.setFillColor(sf::Color::Green);
	text1.setString("Score: " + std::to_string(score));
	text1.setPosition(window.getSize().y, 100);
	window.draw(text1);
}

TEST_CASE("testing player constructor with getters")
{
	{
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120, score = 0;
		Player p(hp, lim_ammo, x_pos, y_pos);
		CHECK(hp == p.GetHealth());
		CHECK(lim_ammo == p.GetLimitAmmo());
		CHECK(ammo == p.GetAmmo());
		CHECK(x_pos == p.GetXPosition());
		CHECK(y_pos == p.GetYPosition());
		CHECK(score == p.GetScore());
	}

	{
		int hp = 10, lim_ammo = 5, ammo = lim_ammo / 2, x_pos = 55, y_pos = 60, score = 0;
		Player p(hp, lim_ammo, x_pos, y_pos);
		CHECK(hp == p.GetHealth());
		CHECK(lim_ammo == p.GetLimitAmmo());
		CHECK(ammo == p.GetAmmo());
		CHECK(x_pos == p.GetXPosition());
		CHECK(y_pos == p.GetYPosition());
		CHECK(score == p.GetScore());
	}
}

TEST_CASE("testing SetScore")
{
	{
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120;
		Player p(hp, lim_ammo, x_pos, y_pos);
		int new_score = 1000;
		p.SetScore(new_score);
		CHECK(hp == p.GetHealth());
		CHECK(lim_ammo == p.GetLimitAmmo());
		CHECK(ammo == p.GetAmmo());
		CHECK(x_pos == p.GetXPosition());
		CHECK(y_pos == p.GetYPosition());
		CHECK(new_score == p.GetScore());
	}

	{
		int hp = 100, lim_ammo = 10, ammo = lim_ammo / 2, x_pos = 110, y_pos = 120;
		Player p(hp, lim_ammo, x_pos, y_pos);
		int new_score = 2000;
		p.SetScore(new_score);
		CHECK(hp == p.GetHealth());
		CHECK(lim_ammo == p.GetLimitAmmo());
		CHECK(ammo == p.GetAmmo());
		CHECK(x_pos == p.GetXPosition());
		CHECK(y_pos == p.GetYPosition());
		CHECK(new_score == p.GetScore());
	}
}