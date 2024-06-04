#pragma once

#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "globals.h"

using namespace sf;

void windowMenu(RenderWindow& window, Text& title, Text& button1, Text& button2);

void windowDifficult (RenderWindow& window, RectangleShape& logOutButton, Text& button1, Text& button2, Text& button3);

void windowGame(RenderWindow& window, RectangleShape& board, Text typeGamelvl[], Text& noticeMessage, 
                Text& timeMessage, RectangleShape& logOutButton, RectangleShape& refreshButton, Clock& clock, int& timer,
                RectangleShape& cube, Text& letter, std::string *letters);

void windowResult(RenderWindow& window, Font& font, Text& titleResult, Text& textSumLetters, Text& textCorrectTypes, Text& textIncorrectTypes, RectangleShape& logOutButton);