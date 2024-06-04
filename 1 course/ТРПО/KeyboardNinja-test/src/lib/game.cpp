#include "game.h"

void initFrame(RectangleShape& board, float xSize, float ySize, float xPos, float yPos) {
    board.setSize(Vector2f(xSize, ySize));      //Размер рамки
    board.setFillColor(Color(0, 0, 0, 0));      //Внутренняя часть рамки прозрачная
    board.setOutlineThickness(2);               //Толщина рамки
    board.setOutlineColor(Color::White);        //Цвет рамки
    xPos = xPos - board.getSize().x / 2;
    yPos = yPos - board.getSize().y / 2;
    board.setPosition(xPos, yPos);              //Позиция рамки
}

void buttonBack(RectangleShape logOutButton, RenderWindow& window) {
    if (Mouse::getPosition().x >= 25 &&
        Mouse::getPosition().y >= 30  &&
        Mouse::getPosition().x <= 25 + logOutButton.getSize().x &&
        Mouse::getPosition().y <= 30 + logOutButton.getSize().y) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            checkMode = 0;
        }
    }
}

void buttonRefresh(RectangleShape refreshButton, RenderWindow& window, RectangleShape& cube, Text& letter) {
    if (Mouse::getPosition().x >= 1835 &&
        Mouse::getPosition().y >= 30  &&
        Mouse::getPosition().x <= 1835 + refreshButton.getSize().x &&
        Mouse::getPosition().y <= 30 + refreshButton.getSize().y) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            sumLetters = 0;
            correctTypes = 0;
            incorrectTypes = 0;            
            flagStart = 0;
            cube.setPosition(945, 110);
            letter.setPosition(945 + 12, 110);
        }
    }
}

void startTimer(Text &timeMessage, Clock& clock, RectangleShape& cube, Text& letter) {
    int timer = clock.getElapsedTime().asSeconds();
    String timerStr = L"Время : " + std::to_string(25 - timer) + L" сек";
    float xPos = 980 - 10 - timeMessage.getGlobalBounds().width / 2;    //Выравнивание по X
    float yPos = 1020 - 20 - timeMessage.getGlobalBounds().height / 2;   //Выравнивание по Y
    timeMessage.setString(timerStr);
    timeMessage.setPosition(xPos, yPos);   //Позиция текста
    
    if (timer >= 25)  {
        clock.restart();
        cube.setPosition(945, 110);
        letter.setPosition(945 + 12, 110);
        checkMode = 3;
        flagStart = 0;
    }
}

void gameKey(RenderWindow& window, RectangleShape& cube, Text& letter, std::string *letters) {
    srand(time(NULL));
    float speedFall = 0;
    switch (numberDifficult) {
        case 0:
            speedFall = 4;
            break;
        case 1:
            speedFall = 8;
            break;
        case 2:
            speedFall = 12;
            break;
    }
    float xPos = rand() % 1220 + 320;
    if (flagCorrect == 0) {
        if (cube.getPosition().y <= 768) {
            cube.move(0, speedFall);
            letter.move(0, speedFall);
        } else if (cube.getPosition().y >= 768) {
            cube.setPosition(xPos, 75);
            numberLetter = rand() % (25 + 1);
            letter.setString(letters[numberLetter]);
            letter.setPosition(xPos + 12, 75);
            incorrectTypes++;
            sumLetters++;
            flagCorrect = 0;
        }
    } else if (flagCorrect != 0) {
            cube.setPosition(xPos, 75);
            numberLetter = rand() % (25 + 1);
            letter.setString(letters[numberLetter]);
            letter.setPosition(xPos + 12, 75);
            flagCorrect = 0;
        }
    window.draw(letter);
    window.draw(cube);
}

void checkCorrect(Event& ev) {
    if (numberLetter == ev.key.code) {
        correctTypes++;
        flagCorrect = 1;
        sumLetters++;
    }
}

