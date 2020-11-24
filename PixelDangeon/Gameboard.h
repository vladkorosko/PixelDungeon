#pragma once
#include"Player.h"

class GameBoard
{
private:
	vector<vector<Place>> map;
	vector<vector<Place>> background;
	vector<Enemy> enemies;
	int x_portal;
	int y_portal;

	bool CheckNotEnemyPosition(const int& x, const int& y) const
	{
		bool res = true;
		for (auto i : enemies)
		{
			int x_pos = i.GetXPosition();
			int y_pos = i.GetYPosition();
			bool cur_res = !Eq(x, y, x_pos / 10, y_pos / 10) && !Eq(x, y, x_pos / 10 - 1, y_pos / 10 - 1)
				&& !Eq(x, y, x_pos / 10 - 1, y_pos / 10) && !Eq(x, y, x_pos / 10, y_pos / 10 - 1);
			res = cur_res && res;
		}
		return res;
	}
	
	bool CheckPosition(const int& x, const int& y, const Player& p) const
	{
		int x_pos = p.GetXPosition();
		int y_pos = p.GetYPosition();
		return map[x][y] != Place::WALL && background[x][y] != Place::TRAP && map[x][y] != Place::INCREASEHP && map[x][y] != Place::IMPROVEBAG
			&& !Eq(x, y, x_pos / 10, y_pos / 10) && !Eq(x, y, x_pos / 10 - 1, y_pos / 10 - 1)
			&& !Eq(x, y, x_pos / 10 - 1, y_pos / 10) && !Eq(x, y, x_pos / 10, y_pos / 10 - 1)
			&& !Eq(x, y, x_portal, y_portal) && !Eq(x, y, x_portal + 1, y_portal + 1)
			&& !Eq(x, y, x_portal, y_portal + 1) && !Eq(x, y, x_portal + 1, y_portal)
			&& CheckNotEnemyPosition(x,y);
	}

public:
	GameBoard(int size, int numenemies)
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
		x_portal = rand() % (size - 3);
		y_portal = rand() % (size - 3);
		x_portal++;
		y_portal++;
		map[x_portal][y_portal] = Place::PORTAL;
		map[x_portal + 1][y_portal] = Place::PORTAL;
		map[x_portal][y_portal + 1] = Place::PORTAL;
		map[x_portal + 1][y_portal + 1] = Place::PORTAL;
		for (int i = 0; i < numenemies; i++)
		{
			int x_pos = rand() % (size - 3) + 2;
			int y_pos = rand() % (size - 3) + 2;
			int hp = rand() % 11 + 15;
			if (CheckNotEnemyPosition(x_pos, y_pos) && CheckNotEnemyPosition(x_pos - 1, y_pos - 1)
				&& CheckNotEnemyPosition(x_pos - 1, y_pos) && CheckNotEnemyPosition(x_pos, y_pos - 1)
				&& !Eq(x_pos, y_pos, x_portal, y_portal) && !Eq(x_pos, y_pos, x_portal + 1, y_portal + 1)
				&& !Eq(x_pos, y_pos, x_portal, y_portal + 1) && !Eq(x_pos, y_pos, x_portal + 1, y_portal))
				enemies.push_back(Enemy(hp, 0, x_pos*10, y_pos*10));
			else i--;
		}
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

	void Draw(sf::RenderWindow& window) const
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
		for (auto i : enemies)
			i.DrawBody(window);
	}

	void DrawVision(sf::RenderWindow& window, const Player& player, const sf::Color wall, const sf::Color free, const sf::Color trap) const
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
		for (auto i : enemies)
			i.DrawBody(window);
	}

	void AutoGenerateWalls(int number_of_walls, const Player& player)
	{
		for (int i = 0; i < number_of_walls; i++)
		{
			int x = rand() % map.size();
			int y = rand() % map.size();
			int x_pos = player.GetXPosition();
			int y_pos = player.GetYPosition();

			if (CheckPosition(x,y,player))
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

			if (CheckPosition(x,y,player))
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

			if (CheckPosition(x,y,player))
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

			if (CheckPosition(x,y,player))
				map[x][y] = Place::IMPROVEBAG;
			else i--;
		}
	}
};

void Magic(int x, int y, Player& player, GameBoard& board);
bool Exit();
void CheckCurrentPositionEnemy(GameBoard& Map, Enemy& enemy);
void CheckCurrentPositionPlayer(GameBoard& Map, Enemy& player);
void Move(GameBoard& Map, Enemy& enemy, int key, void(*CheckCurrentPosition)(GameBoard&, Enemy&));

void Game(sf::RenderWindow& window, Player& p);
void Menu(sf::RenderWindow &window);