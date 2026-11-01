#include <SFML/Graphics.hpp>
#pragma once
#include <string>
#include <cmath>


class Game {
public:
    Game();
    void run();
private:
    void processEvents();
    void update(float dt);
    void render();
    void updateView();
    static constexpr float WIDTH = 1200.f;
    static constexpr float HEIGHT = 1800.f;

    sf::RenderWindow window;
    sf::RectangleShape box;
    sf::Texture bgTexture;//Menu Texture
    sf::Sprite bgSprite;

    sf::Texture star1;           //STAR TEXTUREs
    sf::Sprite star1_sprite_;
    sf::Texture star2;
    sf::Sprite star2_sprite_;
    sf::Texture star3;
    sf::Sprite star3_sprite_;
    sf::Texture star4;
    sf::Sprite star4_sprite_;

    sf:: Texture z1;
    sf::Sprite z1_sprite;
    sf:: Texture z2;
    sf::Sprite z2_sprite;
    sf:: Texture z3;
    sf::Sprite z3_sprite;



    sf::Font font{"assests/Montserrat-ExtraLight.ttf"};
    sf:: Text clockText{font,"", 150};
    std:: string getTime_string();

    //UPDATE STARS
    float life_time;
    void drawStar(sf:: Sprite& s, float speed, float offset);



};