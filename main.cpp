#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace std;

enum class Direction { UP, DOWN, LEFT, RIGHT };

class windowInfo {
  private:
    sf::Texture blockTexture;
    sf::Sprite block;
    sf::Vector2f blockSize;
    sf::VideoMode mode;
    sf::Font font;
    sf::Text scoreTitle;
    sf::Text scoreText;
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
    void setScoreTitle() {
        scoreTitle.setString(" Score:");
        scoreTitle.setFont(font);
        scoreTitle.setCharacterSize(45);
        scoreTitle.setPosition(0.f, 0.f);
    };
    void setScoreText() {
        char const *scoreString = "0";
        scoreText.setString(scoreString);
        scoreText.setFont(font);
        scoreText.setCharacterSize(45);
        scoreText.setPosition(scoreTitle.findCharacterPos(7).x, 0.f);
    };

  public:
    sf::Vector2i fieldSize;
    sf::RenderWindow window;
    void showStartScreen();
    void showGameScreen(vector<sf::Vector2i> &snake, sf::Vector2i &food);
    void updateScore(int &score) {
        char const *scoreString = to_string(score).c_str();
        scoreText.setString(scoreString);
    };
    windowInfo() {
        loadTexture();
        loadFont();
        block.setTexture(blockTexture);
        blockSize.x = block.getLocalBounds().width;
        blockSize.y = block.getLocalBounds().height;
        setInitWindow();
        setScoreTitle();
        setScoreText();
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

void windowInfo::showGameScreen(vector<sf::Vector2i> &snake,
                                sf::Vector2i &food) {
    window.clear();
    window.draw(scoreTitle);
    window.draw(scoreText);

    sf::Vector2f foodPos(food.x * blockSize.x, food.y * blockSize.y);

    block.setPosition(foodPos);

    window.draw(block);

    // draw snake
    for (const sf::Vector2i &body : snake) {
        sf::Vector2f bodyPos(body.x * blockSize.x, body.y * blockSize.y);
        block.setPosition(bodyPos);
        window.draw(block);
    }
}

int main(void) {
    class windowInfo snakeGame;

    // set food posotion
    srand((unsigned)time(NULL));
    sf::Vector2i food(rand() % snakeGame.fieldSize.x,
                      rand() % snakeGame.fieldSize.y);

    // store snake position
    vector<sf::Vector2i> snake = {
        {rand() % snakeGame.fieldSize.x, rand() % snakeGame.fieldSize.y}};

    Direction direction = Direction::RIGHT;

    // snake initial status
    float speed = 0.5f;
    int score = 0;
    bool isStart = false;
    bool isDead = false;

    sf::Event evt;
    sf::Clock clock;

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

                if (isStart) {
                    if (evt.key.code == sf::Keyboard::Up) {
                        direction = Direction::UP;
                    }
                    if (evt.key.code == sf::Keyboard::Down) {
                        direction = Direction::DOWN;
                    }
                    if (evt.key.code == sf::Keyboard::Left) {
                        direction = Direction::LEFT;
                    }
                    if (evt.key.code == sf::Keyboard::Right) {
                        direction = Direction::RIGHT;
                    }
                }
            }
        }

        if (clock.getElapsedTime().asSeconds() >= speed && !isDead) {
            sf::Vector2i head = snake[0];

            if (direction == Direction::UP) {
                head.y--;
            }
            if (direction == Direction::DOWN) {
                head.y++;
            }
            if (direction == Direction::LEFT) {
                head.x--;
            }
            if (direction == Direction::RIGHT) {
                head.x++;
            }

            // set game over situation
            if (head.x < 0 || head.x >= snakeGame.fieldSize.x || head.y < 0 ||
                head.y >= snakeGame.fieldSize.y) {
                isDead = true;
            }

            for (int i = 1; i < snake.size(); i++) {
                if (head == snake[i]) {
                    isDead = true;
                }
            }

            // update snake position
            snake.insert(snake.begin(), head);

            if (!isDead) {
                if (food == head) {
                    srand((unsigned)time(NULL));
                    food = {rand() % snakeGame.fieldSize.x,
                            rand() % snakeGame.fieldSize.y};
                    score++;
                    snakeGame.updateScore(score);
                } else {
                    snake.pop_back();
                }
            }

            if (snake.size() % 11 == 0) speed /= 1.05;

            clock.restart();
        }

        if (!isStart) {
            snakeGame.showStartScreen();
        } else {
            snakeGame.showGameScreen(snake, food);
        }

        snakeGame.window.display();
    }

    return EXIT_SUCCESS;
}