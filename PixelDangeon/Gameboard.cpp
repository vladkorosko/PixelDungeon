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
	int x_pos = x_portal;
	map[x_pos][y_portal] = Place::SPACE;
	map[x_pos][y_portal+1] = Place::SPACE;
	map[x_pos+1][y_portal] = Place::SPACE;
	map[x_pos+1][y_portal + 1] = Place::SPACE;
	map[x][y_portal] = Place::PORTAL;
	map[x][y_portal + 1] = Place::PORTAL;
	map[x + 1][y_portal] = Place::PORTAL;
	map[x + 1][y_portal + 1] = Place::PORTAL;
	this->x_portal = x;
}

void GameBoard::SetYPortal(int y)
{
	int y_pos = y_portal;
	map[x_portal][y_pos] = Place::SPACE;
	map[x_portal][y_pos + 1] = Place::SPACE;
	map[x_portal + 1][y_pos] = Place::SPACE;
	map[x_portal + 1][y_pos + 1] = Place::SPACE;
	map[x_portal][y] = Place::PORTAL;
	map[x_portal][y + 1] = Place::PORTAL;
	map[x_portal + 1][y] = Place::PORTAL;
	map[x_portal + 1][y + 1] = Place::PORTAL;
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
			body.setPosition(static_cast<float>(i * 10), static_cast<float>(j * 10));
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
					body.setPosition(static_cast<float>(x_pos * 10), static_cast<float>(y_pos * 10));
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
			body.setPosition(static_cast<float>(x_e), static_cast<float>(y_e));
			window.draw(body);
		}
		if (abs(x_p - x_e + 5) + abs(y_p - y_e - 5) > 55)
		{
			body.setPosition(static_cast<float>(x_e - 10), static_cast<float>(y_e));
			window.draw(body);
		}
		if (abs(x_p - x_e - 5) + abs(y_p - y_e + 5) > 55)
		{
			body.setPosition(static_cast<float>(x_e), static_cast<float>(y_e - 10));
			window.draw(body);
		}
		if (abs(x_p - x_e + 5) + abs(y_p - y_e + 5) > 55)
		{
			body.setPosition(static_cast<float>(x_e - 10), static_cast<float>(y_e - 10));
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

TEST_CASE("testing point are equals")
{
	CHECK(Eq(1, 1, 1, 1) == true);
	CHECK(Eq(1, 2, 1, 2) == true);
	CHECK(Eq(-1, 1, -1, 1) == true);
	CHECK(Eq(1, -1, 1, -1) == true);
	CHECK(Eq(-1, -1, -1, -1) == true);
	CHECK(Eq(2, 1, 2, 1) == true);
	CHECK(Eq(2, 2, 2, 2) == true);
	CHECK(Eq(10, 23, 10, 23) == true);
	CHECK(Eq(129, 96, 129, 96) == true);

	CHECK(Eq(1, 1, 2, 1) == false);
	CHECK(Eq(1, 2, 1, 1) == false);
	CHECK(Eq(1, 1, 1, 2) == false);
	CHECK(Eq(2, 1, 1, 1) == false);
	CHECK(Eq(-1, 1, 1, 1) == false);
	CHECK(Eq(1, -1, 1, 1) == false);
	CHECK(Eq(1, 1, -1, 1) == false);
	CHECK(Eq(1, 1, 1, -1) == false);

	CHECK(Eq(1, 1, -1, -1) == false);
	CHECK(Eq(-1, -1, 1, 1) == false);

	CHECK(Eq(12, 238, 32, 1238) == false);
	CHECK(Eq(1, 8, 2, 18) == false);
}

TEST_CASE("testing gameboard constructor")
{
	size_t num_enemies = 0, size_board = 10;
	GameBoard g(size_board, num_enemies);
	CHECK(g.GetEnemies().size() == num_enemies);
	std::vector<std::vector<Place>> map = g.GetMap();
	std::vector<std::vector<Place>> back = g.GetBackGround();
	int x_port = g.GetXPortal();
	int y_port = g.GetYPortal();
	CHECK(map.size() == size_board);
	CHECK(back.size() == size_board);
	if (map.size())
	{
		CHECK(map[0].size() == size_board);
		CHECK(back[0].size() == size_board);
	}
	for (size_t i = 0; i < size_board; i++)
		for (size_t j = 0; j < size_board; j++)
		{
			CHECK(back[i][j] == Place::SPACE);
			if (i == 0 || j == 0 || i == size_board - 1 || j == size_board - 1)
				CHECK(map[i][j] == Place::WALL);
			else if ((i == x_port && j == y_port) || (i == x_port && j == y_port + 1) || (i == x_port + 1 && j == y_port) || (i == x_port + 1 && j == y_port + 1))
				CHECK(map[i][j] == Place::PORTAL);
			else CHECK(map[i][j] == Place::SPACE);
		}
}

TEST_CASE("testing gameboard setters")
{
	size_t num_enemies = 0, size_board = 10;
	GameBoard g(size_board, num_enemies);
	int x_port = 7, y_port = 7;
	g.SetXPortal(x_port);
	g.SetYPortal(y_port);
	CHECK(x_port == g.GetXPortal());
	CHECK(y_port == g.GetYPortal());
	{
		std::vector<std::vector<Place>> map = g.GetMap();
		std::vector<std::vector<Place>> back = g.GetBackGround();
		for (size_t i = 0; i < size_board; i++)
			for (size_t j = 0; j < size_board; j++)
			{
				CHECK(back[i][j] == Place::SPACE);
				if (i == 0 || j == 0 || i == size_board - 1 || j == size_board - 1)
					CHECK(map[i][j] == Place::WALL);
				else if ((i == x_port && j == y_port) || (i == x_port && j == y_port + 1) || (i == x_port + 1 && j == y_port) || (i == x_port + 1 && j == y_port + 1))
					CHECK(map[i][j] == Place::PORTAL);
				else CHECK(map[i][j] == Place::SPACE);
			}
	}
	{
		int x_pos_trap = 1, y_pos_trap = 2;
		Place p_back = Place::TRAP;
		Place p_map = Place::IMPROVEBAG;
		g.SetBackGroundElement(x_pos_trap, y_pos_trap, p_back);
		g.SetMapElement(y_pos_trap, x_pos_trap, p_map);
		std::vector<std::vector<Place>> map = g.GetMap();
		std::vector<std::vector<Place>> back = g.GetBackGround();
		for (size_t i = 0; i < size_board; i++)
			for (size_t j = 0; j < size_board; j++)
			{
				if (i == x_pos_trap && j == y_pos_trap)
					CHECK(back[i][j] == p_back);
				else
					CHECK(back[i][j] == Place::SPACE);
				if (i == 0 || j == 0 || i == size_board - 1 || j == size_board - 1)
					CHECK(map[i][j] == Place::WALL);
				else if ((i == x_port && j == y_port) || (i == x_port && j == y_port + 1) || (i == x_port + 1 && j == y_port) || (i == x_port + 1 && j == y_port + 1))
					CHECK(map[i][j] == Place::PORTAL);
				else if (j == x_pos_trap && i == y_pos_trap)
					CHECK(map[i][j] == p_map);
				else CHECK(map[i][j] == Place::SPACE);
			}
	}
}