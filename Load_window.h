#include <SFML/Graphics.hpp>
#pragma once

class Game {
public:
    Game();
    void run();
private:
    void processEvents();
    void update(float dt);
    void render();
    void updateView();
    static constexpr float WIDTH = 600.f;
    static constexpr float HEIGHT = 900.f;

    sf::RenderWindow window;
    sf::RectangleShape box;
    sf::Texture bgTexture;
    sf::Sprite bgSprite;



};