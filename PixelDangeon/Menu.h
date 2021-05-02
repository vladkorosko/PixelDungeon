#pragma once
#include "Gameboard.h"
#include "Moving.h"
#include "AI.h"

void NewGame(sf::RenderWindow& window, Player& p);
void ContinueGame(sf::RenderWindow& window, Player& player);
void Menu(sf::RenderWindow& window);
bool Exit();