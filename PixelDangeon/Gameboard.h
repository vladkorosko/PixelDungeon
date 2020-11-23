#pragma once
#include"Player.h"

class GameBoard
{
private:
	vector<vector<Place>> map;
	vector<vector<Place>> background;
	int x_portal;
	int y_portal;

public:
	GameBoard(int size)
	{
		vector<vector<Place>> s(size, (vector<Place>(size, Place::SPACE)));
		background = s;
		for (int i = 0; i < size; i++)
			{
				s[0][i] = Place::WALL;
				s[size - 1][i] = Place::WALL;
				s[i][0] = Place::WALL;
				s[i][size - 1] = Place::WALL;
			}
		map = s;
		srand(time(NULL));
		x_portal = rand() % (size - 3);
		y_portal = rand() % (size - 3);
		map[x_portal][y_portal] = Place::PORTAL;
		map[x_portal + 1][y_portal] = Place::PORTAL;
		map[x_portal][y_portal + 1] = Place::PORTAL;
		map[x_portal + 1][y_portal + 1] = Place::PORTAL;
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

	int GetXPortal() const
	{
		return x_portal;
	}

	int GetYPortal() const
	{
		return y_portal;
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
				case 4:
					body.setFillColor(HiddenImproveBag);
					break;
				default:
					body.setFillColor(Portal);
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
					case 4:
						body.setFillColor(ImproveBag);
						break;
					default:
						body.setFillColor(Portal);
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
				&& !Eq(x, y, x_pos / 10 - 1, y_pos / 10) && !Eq(x, y, x_pos / 10, y_pos / 10 - 1)
				&& !Eq(x, y, x_portal, y_portal) && !Eq(x, y, x_portal + 1, y_portal + 1)
				&& !Eq(x, y, x_portal, y_portal + 1) && !Eq(x, y, x_portal + 1, y_portal))
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
				&& !Eq(x, y, x_pos / 10 - 1, y_pos / 10) && !Eq(x, y, x_pos / 10, y_pos / 10 - 1)
				&& !Eq(x, y, x_portal, y_portal) && !Eq(x, y, x_portal + 1, y_portal + 1)
				&& !Eq(x, y, x_portal, y_portal + 1) && !Eq(x, y, x_portal + 1, y_portal))
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

			if (map[x][y] != Place::WALL && background[x][y] != Place::TRAP && map[x][y] != Place::INCREASEHP
				&& !Eq(x, y, x_pos / 10, y_pos / 10) && !Eq(x, y, x_pos / 10 - 1, y_pos / 10 - 1)
				&& !Eq(x, y, x_pos / 10 - 1, y_pos / 10) && !Eq(x, y, x_pos / 10, y_pos / 10 - 1)
				&& !Eq(x, y, x_portal, y_portal) && !Eq(x, y, x_portal + 1, y_portal + 1)
				&& !Eq(x, y, x_portal, y_portal + 1) && !Eq(x, y, x_portal + 1, y_portal))
				map[x][y] = Place::INCREASEHP;
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

			if (map[x][y] != Place::WALL && background[x][y] != Place::TRAP && map[x][y] != Place::INCREASEHP && map[x][y] != Place::IMPROVEBAG
				&& !Eq(x, y, x_pos / 10, y_pos / 10) && !Eq(x, y, x_pos / 10 - 1, y_pos / 10 - 1)
				&& !Eq(x, y, x_pos / 10 - 1, y_pos / 10) && !Eq(x, y, x_pos / 10, y_pos / 10 - 1)
				&& !Eq(x, y, x_portal, y_portal) && !Eq(x, y, x_portal + 1, y_portal + 1)
				&& !Eq(x, y, x_portal, y_portal + 1) && !Eq(x, y, x_portal + 1, y_portal))
				map[x][y] = Place::IMPROVEBAG;
			else i--;
		}
	}
};

void Magic(int x, int y, Player& player, GameBoard& board);
bool Exit();
void Move(GameBoard &Map, Player& player, int key);

void Game(sf::RenderWindow& window, Player& p);
void Menu(sf::RenderWindow &window);