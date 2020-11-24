#include "Gameboard.h"

int AI(const GameBoard& map, const Player& player, const Enemy& e)
{
	for (int i = -5; i < 5; i++)
		for (int j = -5; j < 5; j++)
		{
			if (i + j > -7 && i + j < 5 && i - j < 6 && i - j >-6)
			{
				int x_pos = i + e.GetXPosition() / 10;
				int y_pos = j + e.GetYPosition() / 10;
				if (x_pos > 0 && y_pos > 0 && x_pos < map.GetMap().size() && y_pos < map.GetMap().size())
				{
					if (Eq(x_pos, y_pos, player.GetXPosition()/10, player.GetYPosition()/10) 
						|| Eq(x_pos, y_pos, player.GetXPosition()/10 - 1, player.GetYPosition()/10 - 1)
						|| Eq(x_pos, y_pos, player.GetXPosition()/10 - 1, player.GetYPosition()/10) 
						|| Eq(x_pos, y_pos, player.GetXPosition()/10, player.GetYPosition()/10 - 1))
					{
						int x = player.GetXPosition() - e.GetXPosition();
						int y = player.GetYPosition() - e.GetYPosition();
						if (abs(x) > abs(y))
							if (x > 0)
								return 3;
							else return 2;
						else
							if (y > 0)
								return 1;
							else return 0;
					}
				}
			}
		}
	return 4;
}