#include "menu.h"

void initText(Text& text, Font& font, int size, String str, float xPos, float yPos,  Color textColor) {
    text.setFont(font);             //Шрифт
    text.setStyle(Text::Bold);      //Толщина шрифта
    text.setCharacterSize(size);    //Размер шрифта
    text.setString(str);            //Текст

    xPos = xPos - 10 - text.getGlobalBounds().width / 2;    //Выравнивание по X
    yPos = yPos - 20 - text.getGlobalBounds().height / 2;   //Выравнивание по Y

    text.setPosition(xPos, yPos);   //Позиция текста
    text.setFillColor(textColor);   //Цвет текста

}

void initButton(RectangleShape& button, float xPos, float yPos, Texture& t, std::string background) {
    button.setSize(Vector2f(64, 64));
    t.loadFromFile(background);
    t.setSmooth(true);
    button.setTexture(&t);
    button.setPosition(xPos, yPos);
}

void MoveUp(Text button[], int& number) {
    if (number - 1 >= -1) {
        button[number].setFillColor(Color::White);
        number--;
        if (number == -1) 
            number = 1;
        button[number].setFillColor(Color::Red);
    }
}

void MoveDown(Text button[], int& number) {
    if (number + 1 >= 1) {
        button[number].setFillColor(Color::White);
        number++;
        if (number == 2) 
            number = 0;
        button[number].setFillColor(Color::Red);
    }
}

void buttonStartCondition(Text buttonMenu[]) {
    if (Mouse::getPosition().x >= 960 - 5 - buttonMenu[0].getGlobalBounds().width / 2 &&
        Mouse::getPosition().y >= 700 - buttonMenu[0].getGlobalBounds().height / 2 &&
        Mouse::getPosition().x <= 960 + buttonMenu[0].getGlobalBounds().width / 2 &&
        Mouse::getPosition().y <= 700 + buttonMenu[0].getGlobalBounds().height / 2) {
        numberButton = 0;
        buttonMenu[0].setFillColor(Color::Red);
        buttonMenu[1].setFillColor(Color::White);
        if (Mouse::isButtonPressed(Mouse::Left)) {
            checkMode = 1;
        }
    }
}

void buttonExitCondition(Text buttonMenu[], RenderWindow& window) {
    if (Mouse::getPosition().x >= 960 - 5 - buttonMenu[1].getGlobalBounds().width / 2 &&
        Mouse::getPosition().y >= 800 - buttonMenu[1].getGlobalBounds().height / 2 &&
        Mouse::getPosition().x <= 960 + buttonMenu[1].getGlobalBounds().width / 2 &&
        Mouse::getPosition().y <= 800 + buttonMenu[1].getGlobalBounds().height / 2) {
        numberButton = 1;
        buttonMenu[1].setFillColor(Color::Red);
        buttonMenu[0].setFillColor(Color::White);
        if (Mouse::isButtonPressed(Mouse::Left)) {
            window.close();
        }
    }
}