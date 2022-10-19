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
    void loadTexture() {
        if (!blockTexture.loadFromFile("block.png")) {
            cout << "block.png is not found." << endl;
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
    windowInfo() {
        loadTexture();
        block.setTexture(blockTexture);
        blockSize.x = block.getLocalBounds().width;
        blockSize.y = block.getLocalBounds().height;
        setInitWindow();
    };
};

int main(void) {
    class windowInfo snakeGame;

    sf::Event evt;

    while (snakeGame.window.isOpen()) {
        // detect I/O event
        if (snakeGame.window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                snakeGame.window.close();
            }
        }
    }

    return EXIT_SUCCESS;
}