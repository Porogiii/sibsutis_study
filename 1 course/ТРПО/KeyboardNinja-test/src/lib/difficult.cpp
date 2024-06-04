#include "difficult.h"

void MoveUpDifficult(Text button[], int& number) {
    if (number - 1 >= -1) {
        button[number].setFillColor(Color::White);
        number--;
        if (number == -1) 
            number = 2;
        button[number].setFillColor(Color::Red);
    }
}

void MoveDownDifficult(Text button[], int& number) {
    if (number + 1 >= 1) {
        button[number].setFillColor(Color::White);
        number++;
        if (number == 3) 
            number = 0;
        button[number].setFillColor(Color::Red);
    }
}

void buttonEasyCondition(Text buttonDifficult[]) {
    if (Mouse::getPosition().x >= 960 - 5 - buttonDifficult[0].getGlobalBounds().width / 2 &&
        Mouse::getPosition().y >= 440 - buttonDifficult[0].getGlobalBounds().height / 2 &&
        Mouse::getPosition().x <= 960 + buttonDifficult[0].getGlobalBounds().width / 2 &&
        Mouse::getPosition().y <= 440 + buttonDifficult[0].getGlobalBounds().height / 2) {
        numberDifficult = 0;
        buttonDifficult[0].setFillColor(Color::Red);
        buttonDifficult[1].setFillColor(Color::White);
        buttonDifficult[2].setFillColor(Color::White);
        if (Mouse::isButtonPressed(Mouse::Left)) {
            checkMode = 2;
        }
    }
}

void buttonNormalCondition(Text buttonDifficult[]) {
    if (Mouse::getPosition().x >= 960 - 5 - buttonDifficult[1].getGlobalBounds().width / 2 &&
        Mouse::getPosition().y >= 540 - buttonDifficult[1].getGlobalBounds().height / 2 &&
        Mouse::getPosition().x <= 960 + buttonDifficult[1].getGlobalBounds().width / 2 &&
        Mouse::getPosition().y <= 540 + buttonDifficult[1].getGlobalBounds().height / 2) {
        numberDifficult = 1;
        buttonDifficult[1].setFillColor(Color::Red);
        buttonDifficult[0].setFillColor(Color::White);
        buttonDifficult[2].setFillColor(Color::White);
        if (Mouse::isButtonPressed(Mouse::Left)) {
            checkMode = 2;
        }
    }
}

void buttonHardCondition(Text buttonDifficult[]) {
    if (Mouse::getPosition().x >= 960 - 5 - buttonDifficult[2].getGlobalBounds().width / 2 &&
        Mouse::getPosition().y >= 630 - buttonDifficult[2].getGlobalBounds().height / 2 &&
        Mouse::getPosition().x <= 960 + buttonDifficult[2].getGlobalBounds().width / 2 &&
        Mouse::getPosition().y <= 630 + buttonDifficult[2].getGlobalBounds().height / 2) {
        numberDifficult = 2;
        buttonDifficult[2].setFillColor(Color::Red);
        buttonDifficult[1].setFillColor(Color::White);
        buttonDifficult[0].setFillColor(Color::White);
        if (Mouse::isButtonPressed(Mouse::Left)) {
            checkMode = 2;
        }
    }
}
