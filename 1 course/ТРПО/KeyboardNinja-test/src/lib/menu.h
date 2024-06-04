#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "globals.h"

using namespace sf;

void initText(Text& text, Font& font, int size, String str, float xPos, float yPos,  Color textColor);

void initButton(RectangleShape& button, float xPos, float yPos, Texture& t, std::string background);

void MoveUp(Text button[], int& number);

void MoveDown(Text button[], int& number);

void buttonStartCondition(Text buttonMenu[]);

void buttonExitCondition(Text buttonMenu[], RenderWindow& window);