#include "Load_window.h"
using namespace std;
using namespace sf;
#include <ctime>
#include <cstdio>
#include <iostream>
#include <algorithm>

Button::Button(const sf::Texture &label_texture, const sf::Texture &glow_texture, sf::Vector2f label_position, sf::Vector2f glow_position):
label(label_texture), glow(glow_texture)


{
    label.setPosition(label_position);
    glow.setPosition(glow_position);
    area= glow.getGlobalBounds();
}

void Button::refresh(const sf::Texture &label_texture, const sf::Texture &glow_texture)
{
    label.setTexture(label_texture,true);
    glow.setTexture(glow_texture,true);
    area=glow.getGlobalBounds();


}

void Button::update(sf::Vector2f mouse, float dt)
{
    float target;
    if (area.contains(mouse))
     target=1.f;
    else
        target= 0.f;

    hover+= (target-hover)*10.f * dt;
    glow.setColor(sf::Color(255,255,255,uint8_t(hover * 255)));

}

void Button::draw(sf::RenderWindow &window) {
    window.draw(glow);
    window.draw(label);
}

Game::Game(): window(sf::VideoMode({600,900}),"EST"), box({100.f,100.f})
             ,
              bgTexture("assests/menu_back.png"),bgSprite(bgTexture),
            Sleep_trend_texture("assests/sleep_trend_screen.png"),Sleep_trend_Sprite(Sleep_trend_texture),

              star1("assests/star1.png"),star1_sprite_(star1),
              star2("assests/star2.png"),star2_sprite_(star2) ,
              star3("assests/star3.png"),star3_sprite_(star3) ,
              star4("assests/star4.png"),star4_sprite_(star4),
              z1("assests/z1.png"), z1_sprite((z1)),
              z2("assests/z2.png"), z2_sprite((z2)),
              z3("assests/z3.png"), z3_sprite((z3)),


              sleep_trend_button("assests/sleep_trend_button.png"), sleep_trend_sprite((sleep_trend_button)),
              sleep_trend_glow("assests/sleep_trend_glow.png"), sleep_glow_sprite((sleep_trend_glow)),
              heap_button("assests/Heap_button.png"), heap_sprite((heap_button)),
              heap_glow("assests/Heap_glow.png"), heap_glow_sprite((heap_glow)),

                heap_vs_button(heap_button,heap_glow, {185.f,1400.f}, {174.f,1382.f}),
                sleep_trend_but(sleep_trend_button, sleep_trend_glow,{185.f,1200.f},{174.f,1182.f} )

{
    clockText.setFillColor(sf::Color(255,240,240));
    clockText.setLetterSpacing(1.3f);
    window.setFramerateLimit(60);
    bgSprite.setScale({WIDTH/bgTexture.getSize().x, HEIGHT/bgTexture.getSize().y});

    updateView();
    compiler c;
    c.compile(sleepMap);

    lines= {
        {"Sleep ",  "hrs", InfoNodeType:: sleepDuration, sf::Color(185,168,255)},
        {"Stress ",  "/10", InfoNodeType:: stressScore, sf::Color(255,143,163)},
        {"Cafeine",  "mg", InfoNodeType:: caffeineMg, sf::Color(255,200,112)},
        {"Screen time ",  "min", InfoNodeType:: screenTime, sf::Color(111,227,230)},
        {"Work ",  "hrs", InfoNodeType:: workHours, sf::Color(142,227,161)}

    };
    load_map_data();
}

void Game::load_map_data()
{
    bucketLabels.clear();
    for (auto& line: lines)
    {
        line.values.clear();
    }

    for (int start=0; start<=90; start+=10)
    {
        int end;
        if (start ==90)
            end=100;
        else
            end=start+9;

        bucketLabels.push_back(to_string(start)+"-"+ to_string (end));

        for (auto& line : lines) {
            double avg= sleepMap.averageValues(static_cast<int>(line.which),start,end);

            if (line.which == InfoNodeType::sleepDuration) {
                avg /= 60;

            }
            line.values.push_back(static_cast<float>(avg));

        }
    }
    for (const auto& line: lines) {
        cout<<line.name<<": ";
        for (float v : line.values)
        {
            cout<<v<<" ";

        }
        cout<<" "<<endl;
    }

}
//GRAPH MAKING START------------------------------
float Game::xForBuckect(int i) const {
    const float pad= 50.f;
    float usable = plotArea.size.x-2 *pad;
    float step= usable / (bucketLabels.size()-1);
    return plotArea.position.x+pad+i*step;
}

float Game::yForValue(float val, float min_val, float max_val) const
{
    const float pad= 50.f;
    float usable= plotArea.size.y-2 * pad;
    float t = (val-min_val)/(max_val-min_val);
    float bottom = plotArea.position.y + plotArea.size.y-pad;
    return bottom-t * usable;
}

void Game::drawGraph()
{
    const GraphLine& line = lines[4]; //1 is stress 2 is caefine 3 is screen time before bed 4 is stress
    float min_val =*min_element(line.values.begin(),line.values.end());
    float max_val= *max_element(line.values.begin(), line.values.end());

    for (int i=0; i<(int) line.values.size(); i++)
    {
        CircleShape dot(8);
        dot.setOrigin({8,8});

        dot.setPosition({xForBuckect(i), yForValue(line.values[i], min_val, max_val)});
        dot.setFillColor(line.color);
        window.draw(dot);

    }
}

//GRAPH MAKING END---------------------------------------
void Game:: drawStar(Sprite& s, float speed, float offset)
{
    float t = 0.5f +0.5f * std::sin(life_time * speed + offset);
    s.setColor(sf::Color(255,255,255,uint8_t(195*t)));
    window.draw(s);
}

string Game::getTime_string() {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    int hour = t->tm_hour % 12;
    if (hour==0) {
        hour=12;
    }
    char buffer[16];
    const char* ampm;
    if (t->tm_hour < 12)
        ampm="am";
    else
        ampm="pm";

    snprintf(buffer,sizeof(buffer),"%d:%02d %s",hour,t->tm_min,ampm);
    return buffer;
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
        else if (const auto* m = event->getIf<Event::MouseButtonPressed>())
        {
            Vector2f p= window.mapPixelToCoords(m->position);
            if (screen== Screen::menu)
            {
                if(sleep_trend_but.area.contains(p))
                {
                    screen=Screen::Sleep_Trends;
                    cout<<"SLEEP TREND BUTTON WORKS"<<endl;
                }

                if(heap_vs_button.area.contains(p))
                {
                    screen=Screen::Heap_vs_Map;
                    cout<<"HEAP BUTTON WORKS"<<endl;
                }
            }
        }
    }
}
void Game::update(float dt)
{
    clockText.setString(getTime_string());
    FloatRect bound= clockText.getLocalBounds();
    clockText.setOrigin({bound.position.x + bound.size.x/2.f,bound.position.y + bound.size.y/2.f
} );
    clockText.setPosition({WIDTH/1.96f, HEIGHT/7.2f});
    life_time+= dt;
    //Mouse hover
    Vector2f mouse;
    mouse=window.mapPixelToCoords(Mouse::getPosition(window));
    //
    // button_hover+= (target - button_hover)*10 * dt;

    // sleep_trend_sprite.setPosition({185.f,1200.f});
    // sleep_glow_sprite.setPosition({97.f,1171.f});
    heap_vs_button.update(mouse, dt);
    sleep_trend_but.update(mouse, dt);
}

void Game::renderMenu()
{
    window.draw(bgSprite);
    drawStar(star1_sprite_,3.f, 0.0f);
    drawStar(star2_sprite_,3.f, 1.6f);
    drawStar(star3_sprite_,3.f, 3.1f);
    drawStar(star4_sprite_,3.f, 4.7f);

    drawStar(z1_sprite,1.5,16.f);
    drawStar(z2_sprite,1.5,8.f);
    drawStar(z3_sprite,1.5,0.f);

    window.draw(clockText);

    heap_vs_button.draw(window);
    sleep_trend_but.draw(window);
}
void Game::renderSleepTrends()
{

    window.draw(Sleep_trend_Sprite);
    drawGraph();

}


void Game::render() {
    window.clear(sf::Color::Black);
    if (screen== Screen::menu)
    {
    renderMenu();
    }
    else if (screen == Screen::Sleep_Trends) {
        renderSleepTrends();
    }

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






