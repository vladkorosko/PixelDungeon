﻿#include "Menu.h"

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1000, 800), "PixelDangeon");
	Menu(window);
	return 0;
}