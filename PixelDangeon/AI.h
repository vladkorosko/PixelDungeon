#pragma once
#include "Moving.h"
#include <mutex>
#include <thread>
#include <functional>

int AI(const GameBoard& map, const Player& player, const Enemy& e);

void MoveEnemies(GameBoard& map, Player& player);

void MoveEnemiesParallel(GameBoard& map, Player& player);