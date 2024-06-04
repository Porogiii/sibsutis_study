#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "globals.h"

using namespace sf;

void MoveUpDifficult(Text button[], int& number);

void MoveDownDifficult(Text button[], int& number);

void buttonEasyCondition(Text buttonDifficult[]);

void buttonNormalCondition(Text buttonDifficult[]);

void buttonHardCondition(Text buttonDifficult[]);
