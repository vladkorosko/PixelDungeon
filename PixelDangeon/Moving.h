#pragma once
#include "Gameboard.h"

/**
  *@file
  *@brief File for description moving of players and enemies
  */

  /**
   * @brief Move player in game
   * @param[out] GameBoard& Map - the map of game
   * @param[out] Player& enemy - the player
   * @param[in] int key - direction to move
   */
void MovePlayer(GameBoard& Map, Player& enemy, int key);

/**
   * @brief Move enemy in game
   * @param[out] GameBoard& Map - the map of game
   * @param[out] Enemy& enemy - the enemy that moves
   * @param[out] Player& enemy - the player
   * @param[in] int key - direction to move
   */
void MoveEnemy(GameBoard& Map, Enemy& enemy, Player& p, int key);

/**
   * @brief Place a block from bag on map
   * @param[in] int x - x coordinate
   * @param[in] int y - y coordinate
   * @param[out] Player& player - the player
   * @param[out] GameBoard& board - the map of game
   */
void Magic(int x, int y, Player& player, GameBoard& board);