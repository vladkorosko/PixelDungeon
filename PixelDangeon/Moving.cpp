#include "Moving.h"

void CheckCurrentPositionPlayer(GameBoard& Map, Player& player)
{
	int x_pos = player.GetXPosition();
	int y_pos = player.GetYPosition();
	if (Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10 - 1] == Place::TRAP)
	{
		player.SetHealth(player.GetHealth() - 10);
		Map.SetMapElement(x_pos / 10 - 1, y_pos / 10 - 1, Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10 - 1]);
		Map.SetBackGroundElement(x_pos / 10 - 1, y_pos / 10 - 1, Place::SPACE);
	}

	if (Map.GetBackGround()[x_pos / 10][y_pos / 10 - 1] == Place::TRAP)
	{
		player.SetHealth(player.GetHealth() - 10);
		Map.SetMapElement(x_pos / 10, y_pos / 10 - 1, Map.GetBackGround()[x_pos / 10][y_pos / 10 - 1]);
		Map.SetBackGroundElement(x_pos / 10, y_pos / 10 - 1, Place::SPACE);
	}

	if (Map.GetBackGround()[x_pos / 10][y_pos / 10] == Place::TRAP)
	{
		player.SetHealth(player.GetHealth() - 10);
		Map.SetMapElement(x_pos / 10, y_pos / 10, Map.GetBackGround()[x_pos / 10][y_pos / 10]);
		Map.SetBackGroundElement(x_pos / 10, y_pos / 10, Place::SPACE);
	}

	if (Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10] == Place::TRAP)
	{
		player.SetHealth(player.GetHealth() - 10);
		Map.SetMapElement(x_pos / 10 - 1, y_pos / 10, Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10]);
		Map.SetBackGroundElement(x_pos / 10 - 1, y_pos / 10, Place::SPACE);
	}

	if (Map.GetMap()[x_pos / 10 - 1][y_pos / 10 - 1] == Place::INCREASEHP)
	{
		player.SetHealth(player.GetHealth() + 10);
		Map.SetMapElement(x_pos / 10 - 1, y_pos / 10 - 1, Place::SPACE);
	}

	if (Map.GetMap()[x_pos / 10][y_pos / 10 - 1] == Place::INCREASEHP)
	{
		player.SetHealth(player.GetHealth() + 10);
		Map.SetMapElement(x_pos / 10, y_pos / 10 - 1, Place::SPACE);
	}

	if (Map.GetMap()[x_pos / 10][y_pos / 10] == Place::INCREASEHP)
	{
		player.SetHealth(player.GetHealth() + 10);
		Map.SetMapElement(x_pos / 10, y_pos / 10, Place::SPACE);
	}

	if (Map.GetMap()[x_pos / 10 - 1][y_pos / 10] == Place::INCREASEHP)
	{
		player.SetHealth(player.GetHealth() + 10);
		Map.SetMapElement(x_pos / 10 - 1, y_pos / 10, Place::SPACE);
	}

	if (Map.GetMap()[x_pos / 10 - 1][y_pos / 10 - 1] == Place::IMPROVEBAG)
	{
		int diff = rand() % 7 - 2;
		int new_lim = player.GetLimitAmmo() + diff;
		int new_ammo = player.GetAmmo() + diff;
		if (new_lim < 0)
			player.SetLimitAmmo(0);
		else player.SetLimitAmmo(new_lim);
		if (new_ammo < 0)
			player.SetAmmo(0);
		else player.SetAmmo(new_ammo);
		Map.SetMapElement(x_pos / 10 - 1, y_pos / 10 - 1, Place::SPACE);
	}

	if (Map.GetMap()[x_pos / 10][y_pos / 10 - 1] == Place::IMPROVEBAG)
	{
		int diff = rand() % 7 - 2;
		int new_lim = player.GetLimitAmmo() + diff;
		int new_ammo = player.GetAmmo() + diff;
		if (new_lim < 0)
			player.SetLimitAmmo(0);
		else player.SetLimitAmmo(new_lim);
		if (new_ammo < 0)
			player.SetAmmo(0);
		else player.SetAmmo(new_ammo);
		Map.SetMapElement(x_pos / 10, y_pos / 10 - 1, Place::SPACE);
	}

	if (Map.GetMap()[x_pos / 10][y_pos / 10] == Place::IMPROVEBAG)
	{
		int diff = rand() % 7 - 2;
		int new_lim = player.GetLimitAmmo() + diff;
		int new_ammo = player.GetAmmo() + diff;
		if (new_lim < 0)
			player.SetLimitAmmo(0);
		else player.SetLimitAmmo(new_lim);
		if (new_ammo < 0)
			player.SetAmmo(0);
		else player.SetAmmo(new_ammo);
		Map.SetMapElement(x_pos / 10, y_pos / 10, Place::SPACE);
	}

	if (Map.GetMap()[x_pos / 10 - 1][y_pos / 10] == Place::IMPROVEBAG)
	{
		int diff = rand() % 7 - 2;
		int new_lim = player.GetLimitAmmo() + diff;
		int new_ammo = player.GetAmmo() + diff;
		if (new_lim < 0)
			player.SetLimitAmmo(0);
		else player.SetLimitAmmo(new_lim);
		if (new_ammo < 0)
			player.SetAmmo(0);
		else player.SetAmmo(new_ammo);
		Map.SetMapElement(x_pos / 10 - 1, y_pos / 10, Place::SPACE);
	}
}

void CheckCurrentPositionEnemy(GameBoard& Map, Enemy& enemy)
{
	int x_pos = enemy.GetXPosition();
	int y_pos = enemy.GetYPosition();
	if (Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10 - 1] == Place::TRAP)
	{
		Map.SetMapElement(x_pos / 10 - 1, y_pos / 10 - 1, Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10 - 1]);
		Map.SetBackGroundElement(x_pos / 10 - 1, y_pos / 10 - 1, Place::SPACE);
	}

	if (Map.GetBackGround()[x_pos / 10][y_pos / 10 - 1] == Place::TRAP)
	{
		Map.SetMapElement(x_pos / 10, y_pos / 10 - 1, Map.GetBackGround()[x_pos / 10][y_pos / 10 - 1]);
		Map.SetBackGroundElement(x_pos / 10, y_pos / 10 - 1, Place::SPACE);
	}

	if (Map.GetBackGround()[x_pos / 10][y_pos / 10] == Place::TRAP)
	{
		Map.SetMapElement(x_pos / 10, y_pos / 10, Map.GetBackGround()[x_pos / 10][y_pos / 10]);
		Map.SetBackGroundElement(x_pos / 10, y_pos / 10, Place::SPACE);
	}

	if (Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10] == Place::TRAP)
	{
		Map.SetMapElement(x_pos / 10 - 1, y_pos / 10, Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10]);
		Map.SetBackGroundElement(x_pos / 10 - 1, y_pos / 10, Place::SPACE);
	}
}

bool CheckNextPositionPlayer(const GameBoard& Map, Player& p, int x1, int y1, int x2, int y2)
{
	if (!Map.CheckNotEnemyPosition(x1/10, y1/10) || !Map.CheckNotEnemyPosition(x2/10, y2/10))
	{
		p.SetHealth(p.GetHealth() - rand() % 10);
		return false;
	}
	return true;
}

bool CheckNextPositionEnemy(const GameBoard& Map, Player& p, int x1, int y1, int x2, int y2)
{
	int x_pos = p.GetXPosition();
	int y_pos = p.GetYPosition();
	if (Eq(x_pos, y_pos, x1, y1) || Eq(x_pos - 10, y_pos - 10, x1, y1) ||
		Eq(x_pos - 10, y_pos, x1, y1) || Eq(x_pos, y_pos - 10, x1, y1) ||
		Eq(x_pos, y_pos, x2, y2) || Eq(x_pos - 10, y_pos - 10, x2, y2) ||
		Eq(x_pos - 10, y_pos, x2, y2) || Eq(x_pos, y_pos - 10, x2, y2))
	{
		return false;
	}

	if (!Map.CheckNotEnemyPosition(x1 / 10, y1 / 10) || !Map.CheckNotEnemyPosition(x2 / 10, y2 / 10))
	{
		return false;
	}
	return true;
}

void MovePlayer(GameBoard &Map, Player& enemy, int key)
{
	int x_pos = enemy.GetXPosition();
	int y_pos = enemy.GetYPosition();
	switch (key)
	{
	case 0:
		if (Map.GetMap()[x_pos / 10][y_pos / 10 - 2] && Map.GetMap()[x_pos / 10 - 1][y_pos / 10 - 2] 
			&& CheckNextPositionPlayer(Map, enemy, x_pos-10, y_pos-20,x_pos,y_pos-20))
		{
			y_pos -= 10;
			enemy.SetYPosition(y_pos);
			CheckCurrentPositionPlayer(Map, enemy);
		}
		break;
	case 1:
		if (Map.GetMap()[x_pos / 10][y_pos / 10 + 1] && Map.GetMap()[x_pos / 10 - 1][y_pos / 10 + 1]
			&& CheckNextPositionPlayer(Map, enemy, x_pos - 10, y_pos + 10, x_pos, y_pos + 10))
		{
			y_pos += 10;
			enemy.SetYPosition(y_pos);
			CheckCurrentPositionPlayer(Map, enemy);
		}
		break;
	case 2:
		if (Map.GetMap()[x_pos / 10 - 2][y_pos / 10] && Map.GetMap()[x_pos / 10 - 2][y_pos / 10 - 1]
			&& CheckNextPositionPlayer(Map, enemy, x_pos - 20, y_pos - 10, x_pos-20, y_pos))
		{
			x_pos -= 10;
			enemy.SetXPosition(x_pos);
			CheckCurrentPositionPlayer(Map, enemy);
		}
		break;
	case 3:
		if (Map.GetMap()[x_pos / 10 + 1][y_pos / 10] && Map.GetMap()[x_pos / 10 + 1][y_pos / 10 - 1]
			&& CheckNextPositionPlayer(Map, enemy, x_pos + 10, y_pos - 10, x_pos + 10, y_pos))
		{
			x_pos += 10;
			enemy.SetXPosition(x_pos);
			CheckCurrentPositionPlayer(Map, enemy);
		}
		break;
	default:
		break;
	}
}

void MoveEnemy(GameBoard& Map, Enemy& enemy, Player& p, int key)
{
	int x_pos = enemy.GetXPosition();
	int y_pos = enemy.GetYPosition();
	switch (key)
	{
	case 0:
		if (Map.GetMap()[x_pos / 10][y_pos / 10 - 2] && Map.GetMap()[x_pos / 10 - 1][y_pos / 10 - 2]
			&& CheckNextPositionEnemy(Map, p, x_pos - 10, y_pos - 20, x_pos, y_pos - 20))
		{
			y_pos -= 10;
			enemy.SetYPosition(y_pos);
			CheckCurrentPositionEnemy(Map, enemy);
		}
		break;
	case 1:
		if (Map.GetMap()[x_pos / 10][y_pos / 10 + 1] && Map.GetMap()[x_pos / 10 - 1][y_pos / 10 + 1]
			&& CheckNextPositionEnemy(Map, p, x_pos - 10, y_pos + 10, x_pos, y_pos + 10))
		{
			y_pos += 10;
			enemy.SetYPosition(y_pos);
			CheckCurrentPositionEnemy(Map, enemy);
		}
		break;
	case 2:
		if (Map.GetMap()[x_pos / 10 - 2][y_pos / 10] && Map.GetMap()[x_pos / 10 - 2][y_pos / 10 - 1]
			&& CheckNextPositionEnemy(Map, p, x_pos - 20, y_pos - 10, x_pos - 20, y_pos))
		{
			x_pos -= 10;
			enemy.SetXPosition(x_pos);
			CheckCurrentPositionEnemy(Map, enemy);
		}
		break;
	case 3:
		if (Map.GetMap()[x_pos / 10 + 1][y_pos / 10] && Map.GetMap()[x_pos / 10 + 1][y_pos / 10 - 1]
			&& CheckNextPositionEnemy(Map, p, x_pos + 10, y_pos - 10, x_pos + 10, y_pos))
		{
			x_pos += 10;
			enemy.SetXPosition(x_pos);
			CheckCurrentPositionEnemy(Map, enemy);
		}
		break;
	default:
		break;
	}
}

void Magic(int x, int y, Player& player, GameBoard& Map)
{
	x = (x / 10) * 10;
	y = (y / 10) * 10;
	int x_pos = player.GetXPosition();
	int y_pos = player.GetYPosition();
	if (x != 0 && y != 0 && x != (Map.GetMap().size() - 1) * 10 && y != (Map.GetMap().size() - 1) * 10)
	{
		if (abs(x - x_pos + 5) + abs(y - y_pos + 5) <= 50)
		{
			if (Map.GetMap()[x / 10][y / 10] == Place::WALL && player.GetLimitAmmo() > player.GetAmmo())
			{
				player.SetAmmo(player.GetAmmo() + 1);
				Map.SetMapElement(x / 10, y / 10, Place::SPACE);
			}
			else if (Map.GetMap()[x / 10][y / 10] == Place::SPACE && (0 < player.GetAmmo()) && Map.CheckNotEnemyPosition(x/10,y/10))
			{
				if (!((x_pos == x && y_pos == y) || (x_pos == x && y_pos - 10 == y) ||
					(x_pos - 10 == x && y_pos - 10 == y) || (x_pos - 10 == x && y_pos == y)))
				{
					player.SetAmmo(player.GetAmmo() - 1);
					Map.SetMapElement(x / 10, y / 10, Place::WALL);
				}
			}
		}
	}
}