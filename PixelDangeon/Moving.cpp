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

void Magic(int x, int y, Player& player, GameBoard& board)
{
	x = (x / 10) * 10;
	y = (y / 10) * 10;
	if (x != 0 && y != 0 && x != (board.GetMap().size() - 1) * 10 && y != (board.GetMap().size() - 1) * 10)
	{
		if (abs(x - player.GetXPosition() + 5) + abs(y - player.GetYPosition() + 5) <= 50)
		{
			player.SetAmmo(player.GetAmmo()-1);
			if (board.GetMap()[x / 10][y / 10] == Place::WALL)
			{
				board.SetMapElement(x / 10, y / 10, Place::SPACE);
				board.SetBackGroundElement(x / 10, y / 10, Place::SPACE);
			}
		}
	}
}