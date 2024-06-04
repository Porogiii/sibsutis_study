#include "window.h"
#include "menu.h"

void windowMenu(RenderWindow& window, Text& title, Text& button1, Text& button2) {
    window.draw(title);     //Заголовок
    window.draw(button1);   //Кнопка "Начать"
    window.draw(button2);   //Кнопка "Выход"
}

void windowDifficult (RenderWindow& window, RectangleShape& logOutButton, Text& button1, Text& button2, Text& button3) {
    window.draw(logOutButton);
    window.draw(button1);   //Кнопка "Легко"
    window.draw(button2);   //Кнопка "Нормально"
    window.draw(button3);   //Кнопка "Сложно"
}

void windowGame(RenderWindow& window, RectangleShape& board, Text typeGamelvl[], Text& noticeMessage, 
                Text& timeMessage, RectangleShape& logOutButton, RectangleShape& refreshButton, Clock& clock, int& timer,
                RectangleShape& cube, Text& letter, std::string *letters) {
    window.draw(board);
    window.draw(typeGamelvl[numberDifficult]);
    if (flagStart != 1) window.draw(noticeMessage);
    else if (flagStart == 1)  {
        startTimer(timeMessage, clock, cube, letter);
        gameKey(window, cube, letter, letters);
        window.draw(timeMessage);
    }
    window.draw(logOutButton);
    window.draw(refreshButton);
}

void windowResult(RenderWindow& window, Font& font, Text& titleResult, Text& textSumLetters, Text& textCorrectTypes, Text& textIncorrectTypes, RectangleShape& logOutButton) {
    initText(textSumLetters, font, 80, L"Количество букв : " + std::to_string(sumLetters), 960, 540, Color::White);
    initText(textCorrectTypes, font, 80, L"Правильных нажатий : " + std::to_string(correctTypes), 960, 640, Color::White);
    initText(textIncorrectTypes, font, 80, L"Неправильных нажатий : " + std::to_string(incorrectTypes), 960, 740, Color::White);
    window.draw(titleResult);
    window.draw(textSumLetters);
    window.draw(textCorrectTypes);
    window.draw(textIncorrectTypes);
    window.draw(logOutButton);
}
