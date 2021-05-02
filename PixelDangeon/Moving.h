#pragma once
#include "Gameboard.h"

void MovePlayer(GameBoard& Map, Player& enemy, int key);
void MoveEnemy(GameBoard& Map, Enemy& enemy, Player& p, int key);
void Magic(int x, int y, Player& player, GameBoard& board);