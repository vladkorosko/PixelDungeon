#include "Gameboard.h"

bool Eq(int x1, int y1, int x2, int y2)
{
	if (x1 == x2 && y1 == y2)
		return true;
	else return false;
}

bool GameBoard::CheckPosition(const int& x, const int& y, const Player& p) const
{
	int x_pos = p.GetXPosition();
	int y_pos = p.GetYPosition();
	return map[x][y] != Place::WALL && background[x][y] != Place::TRAP && map[x][y] != Place::INCREASEHP && map[x][y] != Place::IMPROVEBAG
		&& !Eq(x, y, x_pos / 10, y_pos / 10) && !Eq(x, y, x_pos / 10 - 1, y_pos / 10 - 1)
		&& !Eq(x, y, x_pos / 10 - 1, y_pos / 10) && !Eq(x, y, x_pos / 10, y_pos / 10 - 1)
		&& !Eq(x, y, x_portal, y_portal) && !Eq(x, y, x_portal + 1, y_portal + 1)
		&& !Eq(x, y, x_portal, y_portal + 1) && !Eq(x, y, x_portal + 1, y_portal)
		&& CheckNotEnemyPosition(x, y);
}

bool GameBoard::CheckNotEnemyPosition(const int& x, const int& y) const
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

GameBoard::GameBoard(int size, int numenemies)
{
	std::vector<std::vector<Place>> s(size, (std::vector<Place>(size, Place::SPACE)));
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
			enemies.push_back(Enemy(hp, 0, x_pos * 10, y_pos * 10));
		else i--;
	}
}

void GameBoard::SetMapElement(const int& x, const int& y, const Place& p)
{
	map[x][y] = p;
}

std::vector<std::vector<Place>> GameBoard::GetMap() const
{
	return map;
}

void GameBoard::SetBackGroundElement(const int& x, const int& y, const Place& p)
{
	background[x][y] = p;
}

std::vector<std::vector<Place>> GameBoard::GetBackGround() const
{
	return background;
}

void GameBoard::SetXPortal(int x)
{
	this->x_portal = x;
}

void GameBoard::SetYPortal(int y)
{
	this->y_portal = y;
}

int GameBoard::GetXPortal() const
{
	return x_portal;
}

int GameBoard::GetYPortal() const
{
	return y_portal;
}

void GameBoard::SetEnemyIndex(const Enemy& e, int index)
{
	enemies[index] = e;
}

std::vector<Enemy> GameBoard::GetEnemies() const
{
	return enemies;
}

void GameBoard::Draw(sf::RenderWindow& window) const
{
	for (size_t i = 0; i < map.size(); i++)
		for (size_t j = 0; j < map.size(); j++)
		{
			sf::RectangleShape body;
			body.setSize(sf::Vector2f(10, 10));
			body.setPosition(i * 10, j * 10);
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

void GameBoard::DrawVisionUpdated(sf::RenderWindow& window, Player& p)
{
	int x_p = p.GetXPosition();
	int y_p = p.GetYPosition();
	sf::RectangleShape body;
	body.setSize(sf::Vector2f(10, 10));
	for (int i = -5; i < 5; i++)
		for (int j = -5; j < 5; j++)
		{
			if (i + j > -7 && i + j < 5 && i - j < 6 && i - j >-6)
			{
				int x_pos = i + x_p / 10;
				int y_pos = j + y_p / 10;
				if (x_pos >= 0 && y_pos >= 0 && x_pos < static_cast<int>(map.size()) && y_pos < static_cast<int>(map.size()))
				{
					body.setPosition(x_pos * 10, y_pos * 10);
					switch (map[x_pos][y_pos])
					{
					case 0:
						body.setFillColor(Wall);
						break;
					case 1:
						body.setFillColor(Free);
						break;
					case 2:
						body.setFillColor(Trap);
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
	for (auto i : enemies)
	{
		int x_e = i.GetXPosition();
		int y_e = i.GetYPosition();
		body.setFillColor(sf::Color::Black);
		i.DrawBody(window);
		if (abs(x_p - x_e - 5) + abs(y_p - y_e - 5) > 55)
		{
			body.setPosition(x_e, y_e);
			window.draw(body);
		}
		if (abs(x_p - x_e + 5) + abs(y_p - y_e - 5) > 55)
		{
			body.setPosition(x_e - 10, y_e);
			window.draw(body);
		}
		if (abs(x_p - x_e - 5) + abs(y_p - y_e + 5) > 55)
		{
			body.setPosition(x_e, y_e - 10);
			window.draw(body);
		}
		if (abs(x_p - x_e + 5) + abs(y_p - y_e + 5) > 55)
		{
			body.setPosition(x_e - 10, y_e - 10);
			window.draw(body);
		}
	}
}

void GameBoard::AutoGenerateWalls(int number_of_walls, const Player& player)
{
	for (int i = 0; i < number_of_walls; i++)
	{
		int x = rand() % map.size();
		int y = rand() % map.size();
		int x_pos = player.GetXPosition();
		int y_pos = player.GetYPosition();

		if (CheckPosition(x, y, player))
			map[x][y] = Place::WALL;
		else i--;
	}
}

void GameBoard::AutoGenerateTraps(int number_of_traps, const Player& player)
{
	for (int i = 0; i < number_of_traps; i++)
	{
		int x = rand() % map.size();
		int y = rand() % map.size();
		int x_pos = player.GetXPosition();
		int y_pos = player.GetYPosition();

		if (CheckPosition(x, y, player))
			background[x][y] = Place::TRAP;
		else i--;
	}
}

void GameBoard::AutoGenerateBonusHealth(int number_of_hp, const Player& player)
{
	for (int i = 0; i < number_of_hp; i++)
	{
		int x = rand() % map.size();
		int y = rand() % map.size();
		int x_pos = player.GetXPosition();
		int y_pos = player.GetYPosition();

		if (CheckPosition(x, y, player))
			map[x][y] = Place::INCREASEHP;
		else i--;
	}
}

void GameBoard::AutoGenerateBonusBlocks(int number_of_items, const Player& player)
{
	for (int i = 0; i < number_of_items; i++)
	{
		int x = rand() % map.size();
		int y = rand() % map.size();
		int x_pos = player.GetXPosition();
		int y_pos = player.GetYPosition();

		if (CheckPosition(x, y, player))
			map[x][y] = Place::IMPROVEBAG;
		else i--;
	}
}