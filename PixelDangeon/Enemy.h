#pragma 
#include "Constatnts.h"
#include "doctest.h"

/**
  *@file
  *@brief File for description Enemy Class
  */

/**
 * @brief Class Enemy for description model of enemies for the game
 */
class Enemy
{
protected:
	int health;
	int ammo;
	int limit_ammo;
	int x_pos;
	int y_pos;

public:
	/**
	 * @brief Constructor
	 * @param int hp - number of health points
	 * @param int lim - max number of blocks that can take enemy
	 * @param int x_position - x coordinate on map
	 * @param int y_position - y coordinate on map
	 */
	Enemy(int hp, int lim, int x_position, int y_position);

	/**
	 * @brief Copy constructor
	 * @param const Enemy& e - an enemy to copy
	 */
	void operator=(const Enemy& e);

	/**
	 * @brief Setting health
	 * @param const int& hp - new number of health points
	 */
	void SetHealth(const int& hp);

	/**
	 * @brief Getting number of health points
	 * @return number of health points
	 */
	int GetHealth() const;

	/**
	 * @brief Setting health
	 * @param const int& hp - new number of health points
	 */
	void SetAmmo(const int& ammo);

	/**
	 * @brief Getting number of blocks in bag
	 * @return number of blocks
	 */
	int GetAmmo() const;

	/**
	 * @brief Setting limit of blocks
	 * @param const int& limit_ammo - new limit of blocks
	 */
	void SetLimitAmmo(const int& limit_ammo);

	/**
	 * @brief Getting limit of blocks
	 * @return limit of blocks
	 */
	int GetLimitAmmo() const;

	/**
	 * @brief Setting x coordinate
	 * @param const int& x - new x coordinate
	 */
	void SetXPosition(const int& x);

	/**
	 * @brief Getting x coordinate
	 * @return x coordinate of enemy
	 */
	int GetXPosition() const;

	/**
	 * @brief Setting y coordinate
	 * @param const int& y - new y coordinate
	 */
	void SetYPosition(const int& y);

	/**
	 * @brief Getting y coordinate
	 * @return y coordinate of enemy
	 */
	int GetYPosition() const;

	/**
	 * @brief Show enemy on map
	 * @param[out] sf::RenderWindow& window - the window of game
	 */
	void DrawBody(sf::RenderWindow& window) const;

	/**
	 * @brief Show enemies characteristics on your screen
	 * @param[out] sf::RenderWindow& window - the window of game
	 */
	void DrawCharacteristics(sf::RenderWindow& window) const;
};