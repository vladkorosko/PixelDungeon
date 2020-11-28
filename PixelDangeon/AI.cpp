#include "Gameboard.h"

int AI(const GameBoard& map, const Player& player, const Enemy& e)
{
	int x = player.GetXPosition() - e.GetXPosition() - 5;
	int y = player.GetYPosition() - e.GetYPosition() - 5;
	if (abs(x) + abs(y) <= 75)
	{
		if (abs(x) > abs(y))
			if (x > 0)
				return 3;
			else return 2;
		else
			if (y > 0)
				return 1;
			else return 0;
	}
	return 5;
}