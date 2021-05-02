#pragma once
#include "Enemy.h"

class Player: public Enemy
{
private:
	int score = 0;
public:
	Player(int hp, int lim, int x_position, int y_position);

	void SetScore(int sc);

	int GetScore() const;

	void DrawBody(sf::RenderWindow& window) const;

	void DrawCharacteristics(sf::RenderWindow& window) const;
};