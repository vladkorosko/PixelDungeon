#include "Structs.h"

void Move(GameBoard &Map, Player &player, int key)
{
	int x_pos = player.GetXPosition();
	int y_pos = player.GetYPosition();
	switch (key)
	{
	case 0:
		if (Map.GetMap()[x_pos / 10][y_pos / 10 - 2] && Map.GetMap()[x_pos / 10 - 1][y_pos / 10 - 2])
		{
			y_pos -= 10;
			player.SetYPosition(y_pos);
			if (Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10 - 1] == Place::TRAP || Map.GetBackGround()[x_pos / 10][y_pos / 10 - 1] == Place::TRAP)
			{
				player.SetHealth(player.GetHealth()-10);
				Map.SetMapElement(x_pos / 10 - 1, y_pos / 10 - 1, Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10 - 1]);
				Map.SetMapElement(x_pos / 10, y_pos / 10 - 1, Map.GetBackGround()[x_pos / 10][y_pos / 10 - 1]);
				Map.SetBackGroundElement(x_pos / 10, y_pos / 10 - 1, Place::SPACE);
				Map.SetBackGroundElement(x_pos / 10 - 1, y_pos / 10 - 1, Place::SPACE);
			}
		}
		break;
	case 1:
		if (Map.GetMap()[x_pos / 10][y_pos / 10 + 1] && Map.GetMap()[x_pos / 10 - 1][y_pos / 10 + 1])
		{
			y_pos += 10;
			player.SetYPosition(y_pos);
			if (Map.GetBackGround()[x_pos / 10][y_pos / 10] == Place::TRAP || Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10] == Place::TRAP)
			{
				player.SetHealth(player.GetHealth() - 10);
				Map.SetMapElement(x_pos / 10, y_pos / 10, Map.GetBackGround()[x_pos / 10][y_pos / 10]);
				Map.SetMapElement(x_pos / 10 - 1, y_pos / 10, Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10]);
				Map.SetBackGroundElement(x_pos / 10, y_pos / 10, Place::SPACE);
				Map.SetBackGroundElement(x_pos / 10 - 1, y_pos / 10, Place::SPACE);
			}
		}
		break;
	case 2:
		if (Map.GetMap()[x_pos / 10 - 2][y_pos / 10] && Map.GetMap()[x_pos / 10 - 2][y_pos / 10 - 1])
		{
			x_pos -= 10;
			player.SetXPosition(x_pos);
			if (Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10 - 1] == Place::TRAP || Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10] == Place::TRAP)
			{
				player.SetHealth(player.GetHealth() - 10);
				Map.SetMapElement(x_pos / 10 - 1, y_pos / 10 - 1, Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10 - 1]);
				Map.SetMapElement(x_pos / 10 - 1, y_pos / 10, Map.GetBackGround()[x_pos / 10 - 1][y_pos / 10]);
				Map.SetBackGroundElement(x_pos / 10 - 1, y_pos / 10, Place::SPACE);
				Map.SetBackGroundElement(x_pos / 10 - 1, y_pos / 10 - 1, Place::SPACE);
			}
		}
		break;
	case 3:
		if (Map.GetMap()[x_pos / 10 + 1][y_pos / 10] && Map.GetMap()[x_pos / 10 + 1][y_pos / 10 - 1])
		{
			x_pos += 10;
			player.SetXPosition(x_pos);
			if (Map.GetBackGround()[x_pos / 10][y_pos / 10] == Place::TRAP || Map.GetBackGround()[x_pos / 10][y_pos / 10 - 1] == Place::TRAP)
			{
				player.SetHealth(player.GetHealth() - 10);
				Map.SetMapElement(x_pos / 10, y_pos / 10, Map.GetBackGround()[x_pos / 10][y_pos / 10]);
				Map.SetMapElement(x_pos / 10, y_pos / 10 - 1, Map.GetBackGround()[x_pos / 10][y_pos / 10 - 1]);
				Map.SetBackGroundElement(x_pos / 10, y_pos / 10, Place::SPACE);
				Map.SetBackGroundElement(x_pos / 10, y_pos / 10 - 1, Place::SPACE);
			}
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
			if (Map.GetMap()[x / 10][y / 10] == Place::WALL)
			{
				player.SetAmmo(player.GetAmmo() + 1);
				Map.SetMapElement(x / 10, y / 10, Place::SPACE);
			}
			else if (Map.GetMap()[x / 10][y / 10] == Place::SPACE)
			{
				if (Map.GetMap()[x_pos / 10][y_pos / 10] == Place::TRAP || Map.GetMap()[x_pos / 10][y_pos / 10 - 1] == Place::TRAP ||
					Map.GetMap()[x_pos / 10 - 1][y_pos / 10 - 1] == Place::TRAP || Map.GetMap()[x_pos / 10 - 1][y_pos / 10] == Place::TRAP)
				{
					player.SetAmmo(player.GetAmmo() - 1);
					Map.SetMapElement(x / 10, y / 10, Place::WALL);
				}
			}
		}
	}
}