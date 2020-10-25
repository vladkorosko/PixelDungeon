#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <random>
#include <math.h>
#include "SFML/Graphics.hpp"

using namespace std;

bool Eq(int x1, int y1, int x2, int y2);

enum Place
{
	Wall,
	Free,
	Trap

};

struct Player
{
	int health;
	int ammo;
	int x_pos;
	int y_pos;

	Player(int hp, int x_position, int y_position)
	{
		health = hp;
		ammo = 10;
		x_pos = x_position;
		y_pos = y_position;
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
		text1.setCharacterSize(50);
		text1.setFont(font);
		text1.setFillColor(sf::Color::Blue);
		text1.setStyle(sf::Text::Bold);
		text1.setString(to_string(health));
		text1.setPosition(1000, 110);
		window.draw(text1);

		text1.setFillColor(sf::Color::Red);
		text1.setString(to_string(ammo));
		text1.setPosition(1000, 310);
		window.draw(text1);
	}
};

struct GameBoard
{
	vector<vector<Place>> Map;
	vector<vector<Place>> BackGround;

	GameBoard(int size)
	{
		vector<vector<Place>> s(size, (vector<Place>(size, Place::Free)));
		for (int i = 0; i < size; i++)
			{
				s[0][i] = Place::Wall;
				s[size - 1][i] = Place::Wall;
				s[i][0] = Place::Wall;
				s[i][size - 1] = Place::Wall;
			}
		Map = s;
		BackGround = s;
	}

	void Draw(sf::RenderWindow& window)
	{
		for (int i = 0; i < Map.size(); i++)
			for (int j = 0; j < Map.size(); j++)
			{
				sf::Color Wall = sf::Color::Color(47, 79, 79, 255);
				sf::Color Free = sf::Color::Color(218, 165, 32, 255);
				sf::Color Trap = sf::Color::Color(255, 69, 0, 255);
				sf::RectangleShape body;
				body.setSize(sf::Vector2f(10, 10));
				body.setPosition(i*10, j*10);
				switch (Map[i][j])
				{
				case 0:
					body.setFillColor(Wall);
					break;
				case 1:
					body.setFillColor(Free);
					break;
				default:
					body.setFillColor(Trap);
					break;
				}
				window.draw(body);
			}
	}

	void DrawVision(sf::RenderWindow& window, Player player)
	{
		sf::RectangleShape back;
		back.setSize(sf::Vector2f(1000, 1000));
		back.setPosition(0,0);
		back.setFillColor(sf::Color::Color(128, 128, 128, 255));
		window.draw(back);
		for (int i = 0; i < Map.size(); i++)
			for (int j = 0; j < Map.size(); j++)
			{
				if (abs(10 * i - player.x_pos+5) + abs(j * 10  - player.y_pos+5) <= 50)
				{
					sf::Color Wall = sf::Color::Color(47, 79, 79, 255);
					sf::Color Free = sf::Color::Color(218, 165, 32, 255);
					sf::Color Trap = sf::Color::Color(255, 69, 0, 255);
					sf::RectangleShape body;
					body.setSize(sf::Vector2f(10, 10));
					body.setPosition(i * 10, j * 10);
					switch (Map[i][j])
					{
					case 0:
						body.setFillColor(Wall);
						break;
					case 1:
						body.setFillColor(Free);
						break;
					default:
						body.setFillColor(Trap);
						break;
					}
					window.draw(body);
				}
			}
	}

	void AutoGenerateWalls(int number_of_walls, Player player)
	{
		for (int i = 0; i < number_of_walls; i++)
		{
			int x = rand() % Map.size();
			int y = rand() % Map.size();
			if (Map[x][y] != Place::Wall && BackGround[x][y] != Place::Trap
				&& !Eq(x, y, player.x_pos / 10, player.y_pos / 10) && !Eq(x, y, player.x_pos / 10 - 1, player.y_pos / 10 - 1)
				&& !Eq(x, y, player.x_pos / 10 - 1, player.y_pos / 10) && !Eq(x, y, player.x_pos / 10, player.y_pos / 10 - 1))
			{
				Map[x][y] = Place::Wall;
				BackGround[x][y] = Place::Wall;
			}
			else i--;
		}
	}
	
	void AutoGenerateTraps(int number_of_walls, Player player)
	{
		for (int i = 0; i < number_of_walls; i++)
		{
			int x = rand() % Map.size();
			int y = rand() % Map.size();
			if (Map[x][y] != Place::Wall && BackGround[x][y] != Place::Trap
				&& !Eq(x, y, player.x_pos / 10, player.y_pos / 10) && !Eq(x, y, player.x_pos / 10 - 1, player.y_pos / 10 - 1)
				&& !Eq(x, y, player.x_pos / 10 - 1, player.y_pos / 10) && !Eq(x, y, player.x_pos / 10, player.y_pos / 10 - 1))
				BackGround[x][y] = Place::Trap;
			else i--;
		}
	}
};

void Magic(int x, int y, Player& player, GameBoard& board);
bool Exit();
void Move(GameBoard &Map, Player& player, int key);