#include "Structs.h"

void Move(GameBoard &Map, Player &player, int key)
{
	switch (key)
	{
	case 0:
		if (Map.Map[player.x_pos / 10][player.y_pos / 10 - 2] && Map.Map[player.x_pos / 10 - 1][player.y_pos / 10 - 2])
		{
			player.y_pos -= 10;
			if (Map.BackGround[player.x_pos / 10][player.y_pos / 10] == Place::Trap || Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10 - 1] == Place::Trap
				|| Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10] == Place::Trap || Map.BackGround[player.x_pos / 10][player.y_pos / 10 - 1] == Place::Trap)
			{
				player.health -= 10;
				Map.Map[player.x_pos / 10][player.y_pos / 10] = Map.BackGround[player.x_pos / 10][player.y_pos / 10];
				Map.Map[player.x_pos / 10 - 1][player.y_pos / 10 - 1] = Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10 - 1];
				Map.Map[player.x_pos / 10 - 1][player.y_pos / 10] = Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10];
				Map.Map[player.x_pos / 10][player.y_pos / 10 - 1] = Map.BackGround[player.x_pos / 10][player.y_pos / 10 - 1];
				Map.BackGround[player.x_pos / 10][player.y_pos / 10] = Place::Free;
				Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10] = Place::Free;
				Map.BackGround[player.x_pos / 10][player.y_pos / 10 - 1] = Place::Free;
				Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10 - 1] = Place::Free;
			}
		}
		break;
	case 1:
		if (Map.Map[player.x_pos / 10][player.y_pos / 10 + 1] && Map.Map[player.x_pos / 10 - 1][player.y_pos / 10 + 1])
		{
			player.y_pos += 10;
			if (Map.BackGround[player.x_pos / 10][player.y_pos / 10] == Place::Trap || Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10 - 1] == Place::Trap
				|| Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10] == Place::Trap || Map.BackGround[player.x_pos / 10][player.y_pos / 10 - 1] == Place::Trap)
			{
				player.health -= 10;
				Map.Map[player.x_pos / 10][player.y_pos / 10] = Map.BackGround[player.x_pos / 10][player.y_pos / 10];
				Map.Map[player.x_pos / 10 - 1][player.y_pos / 10 - 1] = Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10 - 1];
				Map.Map[player.x_pos / 10 - 1][player.y_pos / 10] = Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10];
				Map.Map[player.x_pos / 10][player.y_pos / 10 - 1] = Map.BackGround[player.x_pos / 10][player.y_pos / 10 - 1];
				Map.BackGround[player.x_pos / 10][player.y_pos / 10] = Place::Free;
				Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10] = Place::Free;
				Map.BackGround[player.x_pos / 10][player.y_pos / 10 - 1] = Place::Free;
				Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10 - 1] = Place::Free;
			}
		}
		break;
	case 2:
		if (Map.Map[player.x_pos / 10 - 2][player.y_pos / 10] && Map.Map[player.x_pos / 10 - 2][player.y_pos / 10 - 1])
		{
			player.x_pos -= 10;
			if (Map.BackGround[player.x_pos / 10][player.y_pos / 10] == Place::Trap || Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10 - 1] == Place::Trap
				|| Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10] == Place::Trap || Map.BackGround[player.x_pos / 10][player.y_pos / 10 - 1] == Place::Trap)
			{
				player.health -= 10;
				Map.Map[player.x_pos / 10][player.y_pos / 10] = Map.BackGround[player.x_pos / 10][player.y_pos / 10];
				Map.Map[player.x_pos / 10 - 1][player.y_pos / 10 - 1] = Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10 - 1];
				Map.Map[player.x_pos / 10 - 1][player.y_pos / 10] = Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10];
				Map.Map[player.x_pos / 10][player.y_pos / 10 - 1] = Map.BackGround[player.x_pos / 10][player.y_pos / 10 - 1];
				Map.BackGround[player.x_pos / 10][player.y_pos / 10] = Place::Free;
				Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10] = Place::Free;
				Map.BackGround[player.x_pos / 10][player.y_pos / 10 - 1] = Place::Free;
				Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10 - 1] = Place::Free;
			}
		}
		break;
	case 3:
		if (Map.Map[player.x_pos / 10 + 1][player.y_pos / 10] && Map.Map[player.x_pos / 10 + 1][player.y_pos / 10 - 1])
		{
			player.x_pos += 10;
			if (Map.BackGround[player.x_pos / 10][player.y_pos / 10] == Place::Trap || Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10 - 1] == Place::Trap
				|| Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10] == Place::Trap || Map.BackGround[player.x_pos / 10][player.y_pos / 10 - 1] == Place::Trap)
			{
				player.health -= 10;
				Map.Map[player.x_pos / 10][player.y_pos / 10] = Map.BackGround[player.x_pos / 10][player.y_pos / 10];
				Map.Map[player.x_pos / 10 - 1][player.y_pos / 10 - 1] = Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10 - 1];
				Map.Map[player.x_pos / 10 - 1][player.y_pos / 10] = Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10];
				Map.Map[player.x_pos / 10][player.y_pos / 10 - 1] = Map.BackGround[player.x_pos / 10][player.y_pos / 10 - 1];
				Map.BackGround[player.x_pos / 10][player.y_pos / 10] = Place::Free;
				Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10] = Place::Free;
				Map.BackGround[player.x_pos / 10][player.y_pos / 10 - 1] = Place::Free;
				Map.BackGround[player.x_pos / 10 - 1][player.y_pos / 10 - 1] = Place::Free;
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
	if (x != 0 && y != 0 && x != (board.Map.size() - 1) * 10 && y != (board.Map.size() - 1) * 1)
	{
		if (abs(x - player.x_pos + 5) + abs(y - player.y_pos + 5) <= 50)
		{
			player.ammo--;
			if (board.Map[x / 10][y / 10] == Place::Wall)
			{
				board.Map[x / 10][y / 10] = Place::Free;
				board.BackGround[x / 10][y / 10] = Place::Free;
			}
		}
	}
}