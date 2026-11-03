#include "Load_window.h"
using namespace std;
using namespace sf;
#include <ctime>
#include <cstdio>
#include <iostream>




Game::Game(): window(sf::VideoMode({600,900}),"EST"), box({100.f,100.f})
,is_button_hovered(false),
bgTexture("assests/EST_test.png"),bgSprite(bgTexture)
// star1("assests/star1.png"),star1_sprite_(star1),
// star2("assests/star2.png"),star2_sprite_(star2) ,
// star3("assests/star3.png"),star3_sprite_(star3) ,
// star4("assests/star4.png"),star4_sprite_(star4),
// z1("assests/z1.png"), z1_sprite((z1)),
// z2("assests/z2.png"), z2_sprite((z2)),
// z3("assests/z3.png"), z3_sprite((z3)),
// sleep_trend_button("assests/sleep_trend_button.png"), sleep_trend_sprite((sleep_trend_button)),
// sleep_trend_glow("assests/sleep_trend_glow.png"), sleep_glow_sprite((sleep_trend_glow))

{
    // clockText.setFillColor(sf::Color(255,240,222));
    window.setFramerateLimit(60);
    bgSprite.setScale({WIDTH/bgTexture.getSize().x, HEIGHT/bgTexture.getSize().y
});

    updateView();
}
void Game:: drawStar(Sprite& s, float speed, float offset)
{
    float t = 0.5f +0.5f * std::sin(life_time * speed + offset);
    s.setColor(sf::Color(255,255,255,uint8_t(195*t)));
    window.draw(s);
}

// string Game::getTime_string() {
//     time_t now = time(nullptr);
//     tm* t = localtime(&now);
//     int hour = t->tm_hour % 12;
//     if (hour==0) {
//         hour=12;
//     }
//     char buffer[16];
//     snprintf(buffer,sizeof(buffer),"%d:%02d %s",hour,t->tm_min,t->tm_hour <12 ? "am" : "pm");
//     return buffer;
// }

void Game::run()
{
    Clock clock;
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }

}

void Game::processEvents()
{
    while (const auto event = window.pollEvent())
    {
        if (event->is<Event::Closed>())
            window.close();
        else if (event->is<Event::Resized>())
            updateView();
        else if (const auto* m = event->getIf<Event::MouseButtonPressed>())
        {
            Vector2f p= window.mapPixelToCoords(m->position);
            if(button_area.contains(p))
            {
                cout<<"IT WORKS"<<endl;
            }
        }
    }
}
void Game::update(float dt) //
{
//     clockText.setString(getTime_string());
//     FloatRect bound= clockText.getLocalBounds();
//     clockText.setOrigin({bound.position.x + bound.size.x/2.f,bound.position.y + bound.size.y/2.f
// } );
//     clockText.setPosition({WIDTH/2.f, HEIGHT/1.507});
    life_time+= dt;
    //Mouse hover
    Vector2f mouse;
    mouse=window.mapPixelToCoords(Mouse::getPosition(window));
    float target = button_area.contains(mouse) ? 1 : 0;
    button_hover+= (target - button_hover)*10 * dt;

    // sleep_trend_sprite.setPosition({185.f,1300.f});
    // sleep_glow_sprite.setPosition({185.f,1300.f});
}

void Game::render() {
    window.clear(sf::Color::Black);
  window.draw(bgSprite);
   // drawStar(star1_sprite_,3.f, 0.0f);
   //  drawStar(star2_sprite_,3.f, 1.6f);
   //  drawStar(star3_sprite_,3.f, 3.1f);
   //  drawStar(star4_sprite_,3.f, 4.7f);
   //
   //  drawStar(z1_sprite,1.5,16.f);
   //  drawStar(z2_sprite,1.5,8.f);
   //  drawStar(z3_sprite,1.5,0.f);
   //  window.draw(clockText);
    //
    // sleep_glow_sprite.setColor(Color(255,255,255,uint8_t(255 * button_hover)));
    // if (button_hover)
    //     window.draw(sleep_glow_sprite);
    //
    // window.draw(sleep_trend_sprite);
    button_hover=0;




    window.display();
}

void Game::updateView() {
    Vector2u size = window.getSize();
    float winRatio = float(size.x) / size.y;
    float viewRatio = WIDTH / HEIGHT;
    FloatRect vp({0.f, 0.f}, {1.f, 1.f});
    if (winRatio > viewRatio)
        { vp.size.x = viewRatio / winRatio; vp.position.x = (1.f - vp.size.x) / 2.f; }
    else
        { vp.size.y = winRatio / viewRatio; vp.position.y = (1.f - vp.size.y) / 2.f; }
    View view({WIDTH / 2.f, HEIGHT / 2.f}, {WIDTH, HEIGHT});
    view.setViewport(vp);
    window.setView(view);

}





