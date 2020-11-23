#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <random>
#include <math.h>
#include "SFML/Graphics.hpp"

using namespace std;

const sf::Color HiddenWall = sf::Color::Color(47, 79, 79, 255);
const sf::Color Free = sf::Color::Color(218, 165, 32, 255);
const sf::Color Trap = sf::Color::Color(255, 69, 0, 255);
const sf::Color IncreaseHP = sf::Color::Color(0, 255, 255, 255);
const sf::Color ImproveBag = sf::Color::Color(255, 20, 147, 255);
const sf::Color Wall = sf::Color::Color(105, 105, 105, 255);
const sf::Color HiddenTrap = sf::Color::Color(178, 34, 34, 255);
const sf::Color HiddenFree = sf::Color::Color(184, 134, 11, 255);
const sf::Color HiddenIncreaseHP = sf::Color::Color(30, 144, 255, 255);
const sf::Color HiddenImproveBag = sf::Color::Color(199, 21, 133, 255);
const sf::Color Portal = sf::Color::Color(0, 0, 128, 128);

bool Eq(int x1, int y1, int x2, int y2);

enum Place
{
	WALL,
	SPACE,
	TRAP,
	INCREASEHP,
	IMPROVEBAG,
	PORTAL
};