#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace std;

class windowInfo {
  private:
    sf::Texture blockTexture;
    sf::Sprite block;
    sf::Vector2f blockSize;
    sf::VideoMode mode;
    sf::Font font;
    const int titleTextSize = 150;
    const int hintTextSize = 35;
    const float titleOutline = 5.0f;
    void loadTexture() {
        if (!blockTexture.loadFromFile("block.png")) {
            cout << "block.png is not found." << endl;
            exit(1);
        }
    };
    void loadFont() {
        if (!font.loadFromFile("BAUHS93.TTF")) {
            cout << "BAUHS93.TTF is not found." << endl;
            exit(1);
        }
    };
    void setInitWindow() {
        fieldSize.x = 20;
        fieldSize.y = 15;
        const wchar_t *name = L"貪吃蛇";
        mode.width = (unsigned int)(fieldSize.x * blockSize.x);
        mode.height = (unsigned int)(fieldSize.y * blockSize.y);
        window.create(mode, name);
    };

  public:
    sf::Vector2i fieldSize;
    sf::RenderWindow window;
    void showStartScreen();
    windowInfo() {
        loadTexture();
        loadFont();
        block.setTexture(blockTexture);
        blockSize.x = block.getLocalBounds().width;
        blockSize.y = block.getLocalBounds().height;
        setInitWindow();
    };
};

void windowInfo::showStartScreen() {
    const char *title = "START";
    const char *hint = "- Press any key to start -";

    sf::Text start(title, font, titleTextSize);
    sf::Text press_to_start(hint, font, hintTextSize);

    start.setFillColor(sf::Color::Red);
    start.setOutlineColor(sf::Color::Yellow);
    start.setOutlineThickness(titleOutline);

    const float positionX =
        0.5 * (fieldSize.x * blockSize.x - start.getLocalBounds().width);

    const float titlePositionY = 0.22 * fieldSize.y * blockSize.y;

    const float hintPositionY = titlePositionY + 1.1 * start.getCharacterSize();

    start.setPosition(positionX, titlePositionY);
    press_to_start.setPosition(positionX, hintPositionY);

    window.clear();
    window.draw(start);
    window.draw(press_to_start);
}

int main(void) {
    class windowInfo snakeGame;

    bool isStart = false;

    sf::Event evt;

    while (snakeGame.window.isOpen()) {
        // detect I/O event
        if (snakeGame.window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                snakeGame.window.close();
            }
            if (evt.type == sf::Event::KeyPressed) {
                //  play first time
                if (!isStart) {
                    isStart = true;
                }
            }
        }

        if (!isStart) {
            snakeGame.showStartScreen();
        }

        snakeGame.window.display();
    }

    return EXIT_SUCCESS;
}