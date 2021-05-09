#pragma once
#include "Enemy.h"

/**
  *@file
  *@brief File for description of Player Class
  */

  /**
   * @brief Class Player for description model of player for the game
   */
class Player: public Enemy
{
private:
	int score = 0;
public:
	/**
	 * @brief Constructor
	 * @param int hp - number of health points
	 * @param int lim - max number of blocks that you can put into yours player bag
	 * @param int x_position - x coordinate on map
	 * @param int y_position - y coordinate on map
	 */
	Player(int hp, int lim, int x_position, int y_position);

	/**
	 * @brief Setting score
	 * @param int sc - number of points you get on game(score)
	 */
	void SetScore(int sc);

	/**
	 * @brief Getting score
	 * @return the score of player
	 */
	int GetScore() const;

	/**
	 * @brief Show player on map
	 * @param[out] sf::RenderWindow& window - the window of game
	 */
	void DrawBody(sf::RenderWindow& window) const;

	/**
	 * @brief Show players characteristics on your screen
	 * @param[out] sf::RenderWindow& window - the window of game
	 */
	void DrawCharacteristics(sf::RenderWindow& window) const;
};