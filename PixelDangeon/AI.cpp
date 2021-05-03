#include "AI.h"

using namespace std;

int AI(const GameBoard& map, const Player& player, const Enemy& e)
{
	int x = player.GetXPosition() - e.GetXPosition() - 5;
	int y = player.GetYPosition() - e.GetYPosition() - 5;
	int x_pos = e.GetXPosition();
	int y_pos = e.GetYPosition();
	if (abs(x) + abs(y) <= 75)
	{
		if (abs(x) > abs(y))
			if (x > 0)
			{
				if (map.GetMap()[x_pos / 10 + 1][y_pos / 10 - 1] == 0)
				{
					if (map.GetMap()[x_pos / 10][y_pos / 10 + 1] && map.GetMap()[x_pos / 10 - 1][y_pos / 10 + 1])
						return 1;
					if (map.GetMap()[x_pos / 10][y_pos / 10 - 2] && map.GetMap()[x_pos / 10 - 1][y_pos / 10 - 2])
						return 0;
					return 2;
				}
				if (map.GetMap()[x_pos / 10 + 1][y_pos / 10] == 0)
				{
					if (map.GetMap()[x_pos / 10][y_pos / 10 - 2] && map.GetMap()[x_pos / 10 - 1][y_pos / 10 - 2])
						return 0;
					if (map.GetMap()[x_pos / 10][y_pos / 10 + 1] && map.GetMap()[x_pos / 10 - 1][y_pos / 10 + 1])
						return 1;
					return 2;
				}
				return 3;
			}
			else
			{
				if (map.GetMap()[x_pos / 10 - 2][y_pos / 10] == 0)
				{
					if (map.GetMap()[x_pos / 10][y_pos / 10 - 2] && map.GetMap()[x_pos / 10 - 1][y_pos / 10 - 2])
						return 0;
					if (map.GetMap()[x_pos / 10][y_pos / 10 + 1] && map.GetMap()[x_pos / 10 - 1][y_pos / 10 + 1])
						return 1;
					return 3;
				}
				if (map.GetMap()[x_pos / 10 - 2][y_pos / 10 - 1] == 0)
				{
					if (map.GetMap()[x_pos / 10][y_pos / 10 + 1] && map.GetMap()[x_pos / 10 - 1][y_pos / 10 + 1])
						return 1;
					if (map.GetMap()[x_pos / 10][y_pos / 10 - 2] && map.GetMap()[x_pos / 10 - 1][y_pos / 10 - 2])
						return 0;
					return 3;
				}
				return 2;
			}
		else
			if (y > 0)
			{
				if (map.GetMap()[x_pos / 10 - 1][y_pos / 10 + 1] == 0)
				{
					if (map.GetMap()[x_pos / 10 - 2][y_pos / 10 - 1] && map.GetMap()[x_pos / 10 - 2][y_pos / 10])
						return 2;
					if (map.GetMap()[x_pos / 10 + 1][y_pos / 10 - 1] && map.GetMap()[x_pos / 10 + 1][y_pos / 10])
						return 3;
					return 0;
				}
				if (map.GetMap()[x_pos / 10][y_pos / 10 + 1] == 0)
				{
					if (map.GetMap()[x_pos / 10 + 1][y_pos / 10 - 1] && map.GetMap()[x_pos / 10 + 1][y_pos / 10])
						return 3;
					if (map.GetMap()[x_pos / 10 - 2][y_pos / 10 - 1] && map.GetMap()[x_pos / 10 - 2][y_pos / 10])
						return 2;
					return 0;
				}
				return 1;
			}
			else
			{
				if (map.GetMap()[x_pos / 10][y_pos / 10 - 2] == 0)
				{
					if (map.GetMap()[x_pos / 10 - 2][y_pos / 10 - 1] && map.GetMap()[x_pos / 10 - 2][y_pos / 10])
						return 2;
					if (map.GetMap()[x_pos / 10 + 1][y_pos / 10 - 1] && map.GetMap()[x_pos / 10 + 1][y_pos / 10])
						return 3;
					return 0;
				}
				if (map.GetMap()[x_pos / 10 - 1][y_pos / 10 - 2] == 0)
				{
					if (map.GetMap()[x_pos / 10 + 1][y_pos / 10 - 1] && map.GetMap()[x_pos / 10 + 1][y_pos / 10])
						return 3;
					if (map.GetMap()[x_pos / 10 - 2][y_pos / 10 - 1] && map.GetMap()[x_pos / 10 - 2][y_pos / 10])
						return 2;
					return 0;
				}
				return 0;
			}
	}
	return 5;
}
