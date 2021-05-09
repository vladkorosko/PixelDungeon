#include "AI.h"

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

void MoveEnemies(GameBoard& map, Player& player)
{
	for (size_t i = 0; i < map.GetEnemies().size(); i++)
	{
		Enemy new_e = map.GetEnemies()[i];
		MoveEnemy(map, new_e, player, AI(map, player, new_e));
		map.SetEnemyIndex(new_e, i);
	}
}

void MoveEnemiesPart(GameBoard& map, Player& player, size_t start, size_t finish, std::mutex& m)
{
	for (size_t i = start; i < std::min(finish, map.GetEnemies().size()); i++)
	{
		Enemy new_e = map.GetEnemies()[i];
		{
			std::lock_guard<std::mutex> l(m);
			MoveEnemy(map, new_e, player, AI(map, player, new_e));
			map.SetEnemyIndex(new_e, i);
		}
	}
}

void MoveEnemiesParallel(GameBoard& map, Player& player)
{
	std::mutex m;
	std::size_t num_threads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(num_threads);
	std::size_t thread_size = (map.GetEnemies().size() / num_threads) + 1;
	std::size_t start = 0;
	for (std::size_t i = 0; i < num_threads; i++)
	{
		threads[i] = std::thread(MoveEnemiesPart, std::ref(map), std::ref(player), start, start + thread_size, std::ref(m));
		start += thread_size;
	}

	for (std::size_t i = 0; i < num_threads; i++) {
		threads[i].join();
	}
}