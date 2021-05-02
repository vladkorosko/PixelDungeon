#pragma 
#include "Constatnts.h"

class Enemy
{
protected:
	int health;
	int ammo;
	int limit_ammo;
	int x_pos;
	int y_pos;

public:
	Enemy(int hp, int lim, int x_position, int y_position);

	void operator=(const Enemy& e);

	void SetHealth(const int& hp);

	int GetHealth() const;

	void SetAmmo(const int& ammo);

	int GetAmmo() const;

	void SetLimitAmmo(const int& limit_ammo);

	int GetLimitAmmo() const;

	void SetXPosition(const int& x);

	int GetXPosition() const;

	void SetYPosition(const int& y);

	int GetYPosition() const;

	void DrawBody(sf::RenderWindow& window) const;

	void DrawCharacteristics(sf::RenderWindow& window) const;
};