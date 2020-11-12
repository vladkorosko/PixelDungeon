#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <random>
#include <math.h>
#include "SFML/Graphics.hpp"

using namespace std;

const sf::Color HiddenWall = sf::Color::Color(47, 79, 79, 255);
const sf::Color Free = sf::Color::Color(218, 165, 32, 255);
const sf::Color Trap = sf::Color::Color(255, 69, 0, 255);
const sf::Color IncreaseHP = sf::Color::Color(0, 255, 255, 255);
const sf::Color ImproveBag = sf::Color::Color(255, 20, 147, 255);
const sf::Color Wall = sf::Color::Color(105, 105, 105, 255);
const sf::Color HiddenTrap = sf::Color::Color(178, 34, 34, 255);
const sf::Color HiddenFree = sf::Color::Color(184, 134, 11, 255);
const sf::Color HiddenIncreaseHP = sf::Color::Color(30, 144, 255, 255);
const sf::Color HiddenImproveBag = sf::Color::Color(199, 21, 133, 255);

bool Eq(int x1, int y1, int x2, int y2);

enum Place
{
	WALL,
	SPACE,
	TRAP,
	ICREASEHP,
	IMPROVEBAG,
};

class Player
{
private:
	int health;
	int ammo;
	int limit_ammo;
	int x_pos;
	int y_pos;

public:
	Player(int hp, int lim, int x_position, int y_position)
	{
		health = hp;
		ammo = 10;
		limit_ammo = lim;
		x_pos = x_position;
		y_pos = y_position;
	}

	void operator=(const Player& p)
	{
		this->health = p.health;
		this->ammo = p.ammo;
		this->limit_ammo = p.limit_ammo;
		this->x_pos = p.x_pos;
		this->y_pos = p.y_pos;
	}

	void SetHealth(const int& hp)
	{
		this->health = hp;
	}

	int GetHealth() const
	{
		return health;
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

	void SetXPosition(const int& x)
	{
		this->x_pos = x;
	}

	int GetXPosition() const 
	{
		return x_pos;
	}

	void SetYPosition(const int& y)
	{
		this->y_pos = y;
	}

	int GetYPosition() const
	{
		return y_pos;
	}

	void Draw(sf::RenderWindow &window)
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

		sf::Text text1;
		sf::Font font;
		font.loadFromFile("bold.ttf");
		text1.setCharacterSize(25);
		text1.setFont(font);
		text1.setFillColor(sf::Color::Blue);
		text1.setStyle(sf::Text::Bold);
		text1.setString(to_string(health));
		text1.setPosition(1000, 25);
		window.draw(text1);

		text1.setFillColor(sf::Color::Red);
		text1.setString(to_string(ammo) + " (max: " + to_string(limit_ammo) + ")");
		text1.setPosition(1000, 50);
		window.draw(text1);
	}
};

class GameBoard
{
private:
	vector<vector<Place>> map;
	vector<vector<Place>> background;

public:
	GameBoard(int size)
	{
		vector<vector<Place>> s(size, (vector<Place>(size, Place::SPACE)));
		for (int i = 0; i < size; i++)
			{
				s[0][i] = Place::WALL;
				s[size - 1][i] = Place::WALL;
				s[i][0] = Place::WALL;
				s[i][size - 1] = Place::WALL;
			}
		map = s;
		background = s;
	}

	void SetMapElement(const int& x, const int& y, const Place& p)
	{
		map[x][y] = p;
	}

	vector<vector<Place>> GetMap() const
	{
		return map;
	}

	void SetBackGroundElement(const int& x, const int& y, const Place& p)
	{
		background[x][y] = p;
	}

	vector<vector<Place>> GetBackGround() const
	{
		return background;
	}

	void Draw(sf::RenderWindow& window)
	{
		for (int i = 0; i < map.size(); i++)
			for (int j = 0; j < map.size(); j++)
			{
				sf::RectangleShape body;
				body.setSize(sf::Vector2f(10, 10));
				body.setPosition(i*10, j*10);
				switch (map[i][j])
				{
				case 0:
					body.setFillColor(HiddenWall);
					break;
				case 1:
					body.setFillColor(HiddenFree);
					break;
				case 2:
					body.setFillColor(HiddenTrap);
					break;
				case 3:
					body.setFillColor(HiddenIncreaseHP);
					break;
				default:
					body.setFillColor(HiddenImproveBag);
					break;

				}
				window.draw(body);
			}
	}

	void DrawVision(sf::RenderWindow& window, const Player& player, const sf::Color wall, const sf::Color free, const sf::Color trap)
	{
		for (int i = 0; i < map.size(); i++)
			for (int j = 0; j < map.size(); j++)
			{
				if (abs(10 * i - player.GetXPosition()+5) + abs(j * 10  - player.GetYPosition()+5) <= 50)
				{
					sf::RectangleShape body;
					body.setSize(sf::Vector2f(10, 10));
					body.setPosition(i * 10, j * 10);
					switch (map[i][j])
					{
					case 0:
						body.setFillColor(wall);
						break;
					case 1:
						body.setFillColor(free);
						break;
					case 2:
						body.setFillColor(trap);
						break;
					case 3:
						body.setFillColor(IncreaseHP);
						break;
					default:
						body.setFillColor(ImproveBag);
						break;
					}
					window.draw(body);
				}
			}
	}

	void AutoGenerateWalls(int number_of_walls, const Player& player)
	{
		for (int i = 0; i < number_of_walls; i++)
		{
			int x = rand() % map.size();
			int y = rand() % map.size();
			int x_pos = player.GetXPosition();
			int y_pos = player.GetYPosition();

			if (map[x][y] != Place::WALL
				&& !Eq(x, y, x_pos / 10, y_pos / 10) && !Eq(x, y, x_pos / 10 - 1, y_pos / 10 - 1)
				&& !Eq(x, y,  x_pos / 10 - 1, y_pos / 10) && !Eq(x, y, x_pos / 10, y_pos / 10 - 1))
				map[x][y] = Place::WALL;
			else i--;
		}
	}
	
	void AutoGenerateTraps(int number_of_traps, const Player& player)
	{
		for (int i = 0; i < number_of_traps; i++)
		{
			int x = rand() % map.size();
			int y = rand() % map.size();
			int x_pos = player.GetXPosition();
			int y_pos = player.GetYPosition();

			if (map[x][y] != Place::WALL && background[x][y] != Place::TRAP
				&& !Eq(x, y, x_pos / 10, y_pos / 10) && !Eq(x, y, x_pos / 10 - 1, y_pos / 10 - 1)
				&& !Eq(x, y, x_pos / 10 - 1, y_pos / 10) && !Eq(x, y, x_pos / 10, y_pos / 10 - 1))
				background[x][y] = Place::TRAP;
			else i--;
		}
	}

	void AutoGenerateBonusHealth(int number_of_hp, const Player& player)
	{
		for (int i = 0; i < number_of_hp; i++)
		{
			int x = rand() % map.size();
			int y = rand() % map.size();
			int x_pos = player.GetXPosition();
			int y_pos = player.GetYPosition();

			if (map[x][y] != Place::WALL && background[x][y] != Place::TRAP && map[x][y] != Place::ICREASEHP
				&& !Eq(x, y, x_pos / 10, y_pos / 10) && !Eq(x, y, x_pos / 10 - 1, y_pos / 10 - 1)
				&& !Eq(x, y, x_pos / 10 - 1, y_pos / 10) && !Eq(x, y, x_pos / 10, y_pos / 10 - 1))
				map[x][y] = Place::ICREASEHP;
			else i--;
		}
	}

	void AutoGenerateBonusBlocks(int number_of_items, const Player& player)
	{
		for (int i = 0; i < number_of_items; i++)
		{
			int x = rand() % map.size();
			int y = rand() % map.size();
			int x_pos = player.GetXPosition();
			int y_pos = player.GetYPosition();

			if (map[x][y] != Place::WALL && background[x][y] != Place::TRAP && map[x][y] != Place::ICREASEHP && map[x][y] != Place::IMPROVEBAG
				&& !Eq(x, y, x_pos / 10, y_pos / 10) && !Eq(x, y, x_pos / 10 - 1, y_pos / 10 - 1)
				&& !Eq(x, y, x_pos / 10 - 1, y_pos / 10) && !Eq(x, y, x_pos / 10, y_pos / 10 - 1))
				map[x][y] = Place::IMPROVEBAG;
			else i--;
		}
	}
};

void Magic(int x, int y, Player& player, GameBoard& board);
bool Exit();
void Move(GameBoard &Map, Player& player, int key);