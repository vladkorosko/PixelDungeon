#pragma once
#include"Player.h"

bool Eq(int x1, int y1, int x2, int y2);

class GameBoard
{
private:
	std::vector<std::vector<Place>> map;
	std::vector<std::vector<Place>> background;
	std::vector<Enemy> enemies;
	int x_portal;
	int y_portal;

	bool CheckPosition(const int& x, const int& y, const Player& p) const;

public:
	bool CheckNotEnemyPosition(const int& x, const int& y) const;

	GameBoard(int size, int numenemies);

	void SetMapElement(const int& x, const int& y, const Place& p);

	std::vector<std::vector<Place>> GetMap() const;

	void SetBackGroundElement(const int& x, const int& y, const Place& p);

	std::vector<std::vector<Place>> GetBackGround() const;

	void SetXPortal(int x);

	void SetYPortal(int y);

	int GetXPortal() const;

	int GetYPortal() const;

	void SetEnemyIndex(const Enemy& e, int index);

	std::vector<Enemy> GetEnemies() const;

	void Draw(sf::RenderWindow& window) const;

	void DrawVisionUpdated(sf::RenderWindow& window, Player& p);

	void AutoGenerateWalls(int number_of_walls, const Player& player);
	
	void AutoGenerateTraps(int number_of_traps, const Player& player);

	void AutoGenerateBonusHealth(int number_of_hp, const Player& player);

	void AutoGenerateBonusBlocks(int number_of_items, const Player& player);
};

