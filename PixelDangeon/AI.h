#pragma once
#include "Moving.h"
#include <mutex>
#include <thread>
#include <functional>

/**
  *@file
  *@brief File for discription artificial inteligense
  */

  /**
       * @brief Choose the direction for move(AI)
       * @param const GameBoard& map - the map of game
       * @param const Player& player - the player
       * @param const Enemy& e - the enemy that will be moved
       * @return the direction in which to move
       */
int AI(const GameBoard& map, const Player& player, const Enemy& e);

/**
     * @brief Move enemies
     * @param[out] GameBoard& map - the map of game
     * @param[out] Player& player - the player
     */
void MoveEnemies(GameBoard& map, Player& player);

/**
       * @brief Move enemies (multithreaded)
       * @param[out] GameBoard& map - the map of game
       * @param[out] Player& player - the player
       */
void MoveEnemiesParallel(GameBoard& map, Player& player);