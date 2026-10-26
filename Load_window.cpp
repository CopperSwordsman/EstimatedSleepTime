#include "Load_window.h"
using namespace std;
using namespace sf;



Game::Game(): window(sf::VideoMode({600,900}),"EST"), box({100.f,100.f})
, bgTexture("assests/EST_test.png"),bgSprite(bgTexture) {
    window.setFramerateLimit(60);
    bgSprite.setScale({WIDTH/bgTexture.getSize().x, HEIGHT/bgTexture.getSize().y
});

    updateView();
}
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
    }
}
void Game::update(float dt) //
{

}

void Game::render() {
    window.clear(sf::Color::Black);
  window.draw(bgSprite);
    window.display();
}

void Game::updateView() {
    Vector2u size = window.getSize();
    float winRatio = float(size.x) / size.y;
    float viewRatio = WIDTH / HEIGHT;
    FloatRect vp({0.f, 0.f}, {1.f, 1.f});
    if (winRatio > viewRatio) { vp.size.x = viewRatio / winRatio; vp.position.x = (1.f - vp.size.x) / 2.f; }
    else                      { vp.size.y = winRatio / viewRatio; vp.position.y = (1.f - vp.size.y) / 2.f; }
    View view({WIDTH / 2.f, HEIGHT / 2.f}, {WIDTH, HEIGHT});
    view.setViewport(vp);
    window.setView(view);
}




