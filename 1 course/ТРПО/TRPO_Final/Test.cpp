#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

void initText(Text& text, float xpos, float ypos, float windowWidth, float windowHeight, String str, int sizeFont, Color textColor) {
    text.setCharacterSize(sizeFont);
    text.setString(str);

    std::cout << windowHeight << std::endl;
    std::cout << text.getGlobalBounds().height << std::endl;
    
    xpos = xpos - 10 - text.getGlobalBounds().width / 2;
    ypos = ypos - 26 - text.getGlobalBounds().height / 2;
    
    if (xpos < 0) {
        xpos = xpos + text.getGlobalBounds().width / 2;
    }
    else if (xpos > 0 && xpos <= windowWidth / 2) {
        xpos = xpos;
    }
    else if (xpos > xpos - 10 - text.getGlobalBounds().width / 2) 
        xpos = xpos - text.getGlobalBounds().width / 2;


    if (ypos < 0) {
        ypos = ypos + text.getGlobalBounds().height / 2;
    }
    else if (ypos > 0 && ypos <= windowHeight / 2) {
        ypos = ypos;
    }
    else if (ypos > ypos - 26 - text.getGlobalBounds().height / 2) 
        ypos = ypos - text.getGlobalBounds().height / 2;

    text.setPosition(xpos, ypos);
    text.setFillColor(textColor);
}

int main() {
    //Создаём окно
    //
    RenderWindow window;
    window.create(VideoMode::getDesktopMode(), "KeyBoardNinja", Style::Fullscreen);
    //VideoMode::getDesktopMode() - размер окна как стоит по умолчанию в ОС

    //Размер экрана
    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    //Фон экрана меню
    RectangleShape background(Vector2f(width, height));    

    Texture texture_window;
    if (!texture_window.loadFromFile("Pictures/Background.jpg")) return 1;
    background.setTexture(&texture_window);

    //Шрифт
    Font font;
    if (!font.loadFromFile("Font/Raleway/static/Raleway-Thin.ttf")) return 2;

    //Текст
    Text titul;
    titul.setFont(font);
    initText(titul, 960, 200, width, height, "Keyboard W Ninja", 130, Color::Black);

    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            switch (ev.type) {
            case sf::Event::Closed :
                window.close();
            
            case sf::Event::KeyPressed :
                if (ev.key.code == sf::Keyboard::Escape)
                    window.close();
            case sf::Event::MouseButtonPressed :
                if (ev.mouseButton.button == sf::Mouse::Left) {

                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(titul);
        window.display();
    }

    return 0;
}