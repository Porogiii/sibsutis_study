#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <time.h>

using namespace sf;

int checkMode = 0;          //0 - Menu; 1 - Difficult; 2 - Game; 4 - Result
int numberButton = 0;       //0 - Start; 1 - Exit
int numberDifficult = 0;    //0 - Easy; 1 - Normal; 2 - Hard
int flagStart = 0;          //0 - !Start; 1 - Start
int flagCorrect = 0;
int numberLetter;
std::string letters[26];

//Пути для фона кнопок
std::string logOutButtonFile = "Pictures/Button/logout.png";
std::string refreshButtonFile = "Pictures/Button/refresh.png";
std::string restartButtonFile = "Pictures/Button/restart.png";

void initText(Text& text, Font& font, int size, String str, float xPos, float yPos, Color textColor) {
    text.setFont(font);             //Шрифт
    text.setStyle(Text::Bold);      //Толщина шрифта
    text.setCharacterSize(size);    //Размер шрифта
    text.setString(str);            //Текст

    xPos = xPos - 10 - text.getGlobalBounds().width / 2;    //Выравнивание по X
    yPos = yPos - 20 - text.getGlobalBounds().height / 2;   //Выравнивание по Y

    text.setPosition(xPos, yPos);   //Позиция текста
    text.setFillColor(textColor);   //Цвет текста

}

void initFrame(RectangleShape& board, float xSize, float ySize, float xPos, float yPos) {
    board.setSize(Vector2f(xSize, ySize));      //Размер рамки
    board.setFillColor(Color(0, 0, 0, 0));      //Внутренняя часть рамки прозрачная
    board.setOutlineThickness(2);               //Толщина рамки
    board.setOutlineColor(Color::White);        //Цвет рамки
    xPos = xPos - board.getSize().x / 2;
    yPos = yPos - board.getSize().y / 2;
    board.setPosition(xPos, yPos);              //Позиция рамки
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

void buttonBack(RectangleShape logOutButton, RenderWindow& window) {
    if (Mouse::getPosition().x >= 25 &&
        Mouse::getPosition().y >= 30 &&
        Mouse::getPosition().x <= 25 + logOutButton.getSize().x &&
        Mouse::getPosition().y <= 30 + logOutButton.getSize().y) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            checkMode = 0;
        }
    }
}

void buttonRefresh(RectangleShape refreshButton, RenderWindow& window) {
    if (Mouse::getPosition().x >= 1835 &&
        Mouse::getPosition().y >= 30 &&
        Mouse::getPosition().x <= 1835 + refreshButton.getSize().x &&
        Mouse::getPosition().y <= 30 + refreshButton.getSize().y) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            // Изменение текста
        }
    }
}

void startTimer(Text& timeMessage, Clock& clock, RectangleShape& cube, Text& letter) {
    int timer = clock.getElapsedTime().asSeconds();
    String timerStr = L"Время : " + std::to_string(25 - timer) + L" сек";
    float xPos = 980 - 10 - timeMessage.getGlobalBounds().width / 2;    //Выравнивание по X
    float yPos = 1020 - 20 - timeMessage.getGlobalBounds().height / 2;   //Выравнивание по Y
    timeMessage.setString(timerStr);
    timeMessage.setPosition(xPos, yPos);   //Позиция текста

    if (timer >= 25) {
        clock.restart();
        cube.setPosition(945, 110);
        letter.setPosition(945 + 12, 110);
        checkMode = 0;
    }
}

void modeMenu(RenderWindow& window, Event& ev, Text buttonMenu[]) {
    if (checkMode == 0) {
        buttonStartCondition(buttonMenu);
        buttonExitCondition(buttonMenu, window);
        switch (ev.type) {
        case Event::KeyPressed:
            switch (ev.key.code) {
            case Keyboard::Escape:
                window.close();
            case Keyboard::Up:
                MoveUp(buttonMenu, numberButton);
                break;
            case Keyboard::Down:
                MoveDown(buttonMenu, numberButton);
                break;
            case Keyboard::Enter:
                if (numberButton == 0) {
                    checkMode = 1;
                    ev.key.code = Keyboard::Unknown;
                }
                else if (numberButton == 1)
                    window.close();
            }
        }
    }
}

void modeDifficult(RenderWindow& window, Event& ev, Text buttonDifficult[], RectangleShape logOutButton) {
    if (checkMode == 1) {
        buttonBack(logOutButton, window);
        buttonEasyCondition(buttonDifficult);
        buttonNormalCondition(buttonDifficult);
        buttonHardCondition(buttonDifficult);
        switch (ev.type) {
        case Event::KeyPressed:
            switch (ev.key.code) {
            case Keyboard::Escape:
                checkMode = 0;
                numberDifficult = 0;
                break;
            case Keyboard::Up:
                MoveUpDifficult(buttonDifficult, numberDifficult);
                break;
            case Keyboard::Down:
                MoveDownDifficult(buttonDifficult, numberDifficult);
                break;
            case Keyboard::Enter:
                checkMode = 2;
            }
        }
    }
}

void gameKey(RenderWindow& window, RectangleShape& cube, Text& letter) {
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
        }
        else if (cube.getPosition().y >= 768) {
            cube.setPosition(xPos, 75);
            numberLetter = rand() % (25 + 1);
            letter.setString(letters[numberLetter]);
            letter.setPosition(xPos + 12, 75);
            flagCorrect = 0;
        }
    }
    else if (flagCorrect != 0) {
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
        flagCorrect = 1;
    }
}

void modeGame(RenderWindow& window, Event& ev, RectangleShape& logOutButton, RectangleShape& refreshButton, Clock& clock, RectangleShape& cube, Text& letter) {
    if (checkMode == 2) {
        buttonBack(logOutButton, window);
        buttonRefresh(refreshButton, window);
        switch (ev.type) {
        case Event::KeyPressed:
            switch (ev.key.code) {
            case Keyboard::Space:
                flagStart = 1;
                clock.restart();
                break;
            case Keyboard::Escape:
                checkMode = 1;
                flagStart = 0;
                cube.setPosition(945, 110);
                letter.setPosition(945 + 12, 110);
                break;
            default:
                checkCorrect(ev);
                break;
            }
        }
    }
}

void windowMenu(RenderWindow& window, Text& title, Text& button1, Text& button2) {
    window.draw(title);     //Заголовок
    window.draw(button1);   //Кнопка "Начать"
    window.draw(button2);   //Кнопка "Выход"
}

void windowDifficult(RenderWindow& window, RectangleShape& logOutButton, Text& button1, Text& button2, Text& button3) {
    window.draw(logOutButton);
    window.draw(button1);   //Кнопка "Легко"
    window.draw(button2);   //Кнопка "Нормально"
    window.draw(button3);   //Кнопка "Сложно"
}

void windowGame(RenderWindow& window, RectangleShape& board, Text typeGamelvl[], Text& noticeMessage,
    Text& timeMessage, RectangleShape& logOutButton, RectangleShape& refreshButton, Clock& clock, int& timer,
    RectangleShape& cube, Text& letter) {
    window.draw(board);
    window.draw(typeGamelvl[numberDifficult]);
    if (flagStart != 1) window.draw(noticeMessage);
    else if (flagStart == 1) {
        startTimer(timeMessage, clock, cube, letter);
        gameKey(window, cube, letter);
        window.draw(timeMessage);
    }
    window.draw(logOutButton);
    window.draw(refreshButton);
}

int main() {
    //Окно
    RenderWindow window;
    window.create(VideoMode::getDesktopMode(), "KeyBoardNinja", Style::Fullscreen);
    window.setFramerateLimit(60);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Фон меню
    RectangleShape background(Vector2f(1920, 1080));
    Texture screen;
    if (!screen.loadFromFile("Pictures/Background/3.jpg")) return 1;
    background.setTexture(&screen);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Шрифт
    Font font;
    if (!font.loadFromFile("Font/Raleway/static/Raleway-Thin.ttf")) return 2;
    //if (!font.loadFromFile("Font/Mont/mont_extralightdemo.ttf")) return 2;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Заголовок
    Text title;
    initText(title, font, 120, L"Keyboard Ninja", 960, 300, Color::White);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Кнопки
    Text buttonMenu[2];
    initText(buttonMenu[0], font, 70, L"Начать", 960, 700, Color::Red);
    initText(buttonMenu[1], font, 70, L"Выйти", 960, 800, Color::White);

    Text buttonDifficult[3];
    initText(buttonDifficult[0], font, 70, L"Легко", 960, 440, Color::Red);
    initText(buttonDifficult[1], font, 70, L"Нормально", 960, 540, Color::White);
    initText(buttonDifficult[2], font, 70, L"Сложно", 960, 630, Color::White);

    RectangleShape logOutButton;    //Кнопка назад
    Texture logOutTexture;
    initButton(logOutButton, 25, 30, logOutTexture, logOutButtonFile);

    RectangleShape refreshButton;   //Кнопка перезапуска
    Texture refreshTexture;
    initButton(refreshButton, 1835, 30, refreshTexture, refreshButtonFile);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Текст
    Text typeGamelvl[3];
    initText(typeGamelvl[0], font, 80, L"Уровень : Легкий", 960, 920, Color::White);
    initText(typeGamelvl[1], font, 80, L"Уровень : Нормальный", 960, 920, Color::White);
    initText(typeGamelvl[2], font, 80, L"Уровень : Сложный", 960, 920, Color::White);

    Text noticeMessage;
    String noticeMessage_str = L"Отсчет времени начнется после нажатия SPACE";
    initText(noticeMessage, font, 50, noticeMessage_str, 960, 1020, Color::White);

    Text timeMessage;
    timeMessage.setFont(font);
    timeMessage.setStyle(Text::Bold);
    timeMessage.setCharacterSize(60);
    timeMessage.setFillColor(Color::White);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Рамки
    RectangleShape board;

    initFrame(board, 1300, 750, 960, 450);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Таймер

    Clock clock;
    int timer;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Кубик

    RectangleShape cube;
    float xSize = 50, ySize = 50;
    float xPos = 935, yPos = 100;
    initFrame(cube, xSize, ySize, xPos, yPos);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Буквы

    int z = 0;
    for (int i = 'A'; i <= 'Z'; i++) {
        letters[z] = i;
        z++;
    }

    Text letter;
    initText(letter, font, 40, "A", 935 + 10, 100 + 10, Color::White);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    while (window.isOpen()) {
        Event ev;
        while (window.pollEvent(ev)) {
            modeMenu(window, ev, buttonMenu);
            modeDifficult(window, ev, buttonDifficult, logOutButton);
            modeGame(window, ev, logOutButton, refreshButton, clock, cube, letter);
        }

        window.clear();
        window.draw(background);

        switch (checkMode) {
        case 0:
            windowMenu(window, title, buttonMenu[0], buttonMenu[1]);
            break;
        case 1:
            windowDifficult(window, logOutButton, buttonDifficult[0], buttonDifficult[1], buttonDifficult[2]);
            break;
        case 2:
            windowGame(window, board, typeGamelvl, noticeMessage, timeMessage, logOutButton, refreshButton, clock, timer, cube, letter);
            break;
        }

        window.display();
    }

    return 0;
}