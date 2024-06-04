#pragma once

#include <chrono>
#include <thread>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "globals.h"

using namespace sf;

void initFrame(RectangleShape& board, float xSize, float ySize, float xPos, float yPos);

void buttonBack(RectangleShape logOutButton, RenderWindow& window);

void buttonRefresh(RectangleShape refreshButton, RenderWindow& window, RectangleShape& cube, Text& letter);

void startTimer(Text &timeMessage, Clock& clock, RectangleShape& cube, Text& letter);

void gameKey(RenderWindow& window, RectangleShape& cube, Text& letter, std::string *letters);

void checkCorrect(Event& ev);