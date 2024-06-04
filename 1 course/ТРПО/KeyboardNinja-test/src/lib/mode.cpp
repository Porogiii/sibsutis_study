#include "mode.h"

void modeMenu (RenderWindow& window, Event &ev, Text buttonMenu[]) {
    if (checkMode == 0) {
        buttonStartCondition(buttonMenu);
        buttonExitCondition(buttonMenu, window);
        switch (ev.type) {
            case Event::KeyPressed :
                switch (ev.key.code) {
                    case Keyboard::Escape :
                        window.close();
                    case Keyboard::Up :
                        MoveUp(buttonMenu, numberButton);
                        break;
                    case Keyboard::Down :
                        MoveDown(buttonMenu, numberButton);
                        break;
                    case Keyboard::Enter :
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

void modeDifficult (RenderWindow &window, Event &ev, Text buttonDifficult[], RectangleShape logOutButton) {
    if (checkMode == 1) {
        buttonBack(logOutButton, window);
        buttonEasyCondition(buttonDifficult);
        buttonNormalCondition(buttonDifficult);
        buttonHardCondition(buttonDifficult);
        switch (ev.type) {
            case Event::KeyPressed :
                switch (ev.key.code) {
                    case Keyboard::Escape :
                        checkMode = 0;
                        numberDifficult = 0;
                        break;
                    case Keyboard::Up :
                        MoveUpDifficult(buttonDifficult, numberDifficult);
                        break;
                    case Keyboard::Down :
                        MoveDownDifficult(buttonDifficult, numberDifficult);
                        break;
                    case Keyboard::Enter :
                        checkMode = 2;
                }
        }
    }
}

void modeGame(RenderWindow &window, Event &ev, RectangleShape& logOutButton, RectangleShape& refreshButton, Clock& clock, RectangleShape& cube, Text& letter) {
    if (checkMode == 2) {
        buttonBack(logOutButton, window);
        buttonRefresh(refreshButton, window, cube, letter); 
        switch (ev.type) {
            case Event::KeyPressed :
                switch (ev.key.code) {
                    case Keyboard::Space : 
                        flagStart = 1;
                        clock.restart();
                        break;
                    case Keyboard::Escape :
                        checkMode = 1;
                        flagStart = 0;
                        sumLetters = 0;
                        correctTypes = 0;
                        incorrectTypes = 0;
                        cube.setPosition(945, 110);
                        letter.setPosition(945 + 12, 110);
                        break;
                    default :
                        checkCorrect(ev);
                        break;
                }
        }
    }
}

void modeResult(RenderWindow& window, Event& ev, RectangleShape& logOutButton) {
    if (checkMode == 3) {
        buttonBack(logOutButton, window);
        switch (ev.type) {
            case Event::KeyPressed :
                switch (ev.key.code) {
                    case Keyboard::Escape :
                        sumLetters = 0;
                        correctTypes = 0;
                        incorrectTypes = 0;
                        checkMode = 0;
                        break;
                }
        }
    }
}