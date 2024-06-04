#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "difficult.h"
#include "game.h"
#include "globals.h"

using namespace sf;

void modeMenu (RenderWindow& window, Event &ev, Text buttonMenu[]);

void modeDifficult (RenderWindow &window, Event &ev, Text buttonDifficult[], RectangleShape logOutButton);

void modeGame(RenderWindow &window, Event &ev, RectangleShape& logOutButton, RectangleShape& refreshButton, Clock& clock, RectangleShape& cube, Text& letter);

void modeResult(RenderWindow& window, Event& ev, RectangleShape& logOutButton);