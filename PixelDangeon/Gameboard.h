#pragma once
#include"Player.h"

/**
  *@file
  *@brief File for describtion Gameboard Class
  */

bool Eq(int x1, int y1, int x2, int y2);

/**
 * @brief Class GameBoard for description model of map for the game
 */
class GameBoard
{
private:
	std::vector<std::vector<Place>> map;
	std::vector<std::vector<Place>> background;
	std::vector<Enemy> enemies;
	int x_portal;
	int y_portal;

	/**
	 * @brief Checks whether field is empty
	 * @param const int& x - x coordinate of field
	 * @param const int& y - y coordinate of field
	 * @paramconst Player& p - current player
	 * @return true if field is empty
	 */
	bool CheckPosition(const int& x, const int& y, const Player& p) const;

public:

	/**
	 * @brief Checks whether field is not enemy position
	 * @param const int& x - x coordinate of field
	 * @param const int& y - y coordinate of field
	 * @return true if field is not enemy position
	 */
	bool CheckNotEnemyPosition(const int& x, const int& y) const;

	/**
	 * @brief Constructor
	 * @param int size - size of map
	 * @param int numenemies - number of enemies on map
	 */
	GameBoard(int size, int numenemies);

	/**
	 * @brief Setting the map field
	 * @param const int& x - x coordinate of field
	 * @param const int& y - y coordinate of field
	 * @param const Place& p - type of field
	 */
	void SetMapElement(const int& x, const int& y, const Place& p);

	/**
	 * @brief Getting map
	 * @return the map as vector of vectors of Place
	 */
	std::vector<std::vector<Place>> GetMap() const;

	/**
	 * @brief Setting the background field
	 * @param const int& x - x coordinate of field
	 * @param const int& y - y coordinate of field
	 * @param const Place& p - type of field
	 */
	void SetBackGroundElement(const int& x, const int& y, const Place& p);

	/**
	 * @brief Getting map
	 * @return the map as vector of vectors of Place
	 */
	std::vector<std::vector<Place>> GetBackGround() const;

	/**
	 * @brief Setting x coordinate of portal
	 * @param int x - new x coordinate of portal
	 */
	void SetXPortal(int x);

	/**
	 * @brief Setting y coordinate of portal
	 * @param int y - new y coordinate of portal
	 */
	void SetYPortal(int y);

	/**
	 * @brief Getting x coordinate of portal
	 * @return the x coordinate of portal
	 */
	int GetXPortal() const;

	/**
	 * @brief Getting y coordinate of portal
	 * @return the y coordinate of portal
	 */
	int GetYPortal() const;

	/**
	 * @brief Setting the enemy by the index in vector of enemies
	 * @param const Enemy& e - new enemy
	 * @param int index - the index in vector of enemies
	 */
	void SetEnemyIndex(const Enemy& e, int index);

	/**
	 * @brief Getting vector of enemies
	 * @return the vector of enemies
	 */
	std::vector<Enemy> GetEnemies() const;

	/**
	 * @brief Show all map on screen
	 * @param[out] sf::RenderWindow& window - window of game
	 */
	void Draw(sf::RenderWindow& window) const;

	/**
	 * @brief Show players vision on screen
	 * @param[out] sf::RenderWindow& window - window of game
	 */
	void DrawVisionUpdated(sf::RenderWindow& window, Player& p);

	/**
	 * @brief Generates walls in random position if possible
	 * @param int number_of_walls - number of walls to generate
	 * @param const Player& player - the player
	 */
	void AutoGenerateWalls(int number_of_walls, const Player& player);
	
	/**
	 * @brief Generates traps in random position if possible
	 * @param int number_of_traps - number of traps to generate
	 * @param const Player& player - the player
	 */
	void AutoGenerateTraps(int number_of_traps, const Player& player);

	/**
	 * @brief Generates medical kits in random position if possible
	 * @param int number_of_hp - number of medical kits to generate
	 * @param const Player& player - the player
	 */
	void AutoGenerateBonusHealth(int number_of_hp, const Player& player);

	/**
	 * @brief Generates improvements for your bag in random position if possible
	 * @param int number_of_items - number of improvements to generate
	 * @param const Player& player - the player
	 */
	void AutoGenerateBonusBlocks(int number_of_items, const Player& player);
};

