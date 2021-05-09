#pragma once
#include "Gameboard.h"
#include "Moving.h"
#include "AI.h"

/**
  *@file
  *@brief File for menu of game
  */

/**
 * @brief starts new game
 * @param[out] sf::RenderWindow& window - window of game
 * @param[out] Player& p - player
 */
void NewGame(sf::RenderWindow& window, Player& p);

/**
 * @brief Main manu of the game
 * @param[out] sf::RenderWindow& window - window of game
 */
void Menu(sf::RenderWindow& window);