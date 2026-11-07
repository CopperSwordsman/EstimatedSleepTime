#include <SFML/Graphics.hpp>
#pragma once
#include <string>
#include<vector>
#include <cmath>
#include "maps.h"
#include "compile.h"
#include "infonode.h"
#include "Heap.h"


static sf::ContextSettings makeSettings() {
    sf::ContextSettings s;
    s.antiAliasingLevel=8;
    return s;
}
struct GraphLine {
    std::string name;
    std::string unit;
    InfoNodeType which;
    sf::Color color;
    std::vector<float> values;
    bool visible = true;
};



struct Button {
    sf::Sprite label;
    sf::Sprite glow;
    sf::FloatRect area;
    float hover = 0.f;

    Button(const sf::Texture& label_texture, const sf::Texture& glow_texture,
    sf::Vector2f label_position, sf::Vector2f glow_position);

    void refresh(const sf::Texture& label_texture, const sf::Texture& glow_texture);
    void update(sf::Vector2f mouse, float dt,bool keepGlow=false);
    void draw(sf::RenderWindow& window);

};

class Game {
public:
    Game();
    void run();
private:
    CustomMap sleepMap;
    Heap maxHeap{[](const InfoNode &a, const InfoNode &b) {return a.sleepQuality > b.sleepQuality;}};
    Heap minHeap{[](const InfoNode &a, const InfoNode &b) {return a.sleepQuality < b.sleepQuality;}};
    std:: vector<GraphLine> lines;
    std::vector<std::string> bucketLabels;
    void load_map_data();
    enum class Screen {menu, Sleep_Trends, Heap_vs_Map};
    Screen screen=Screen::menu;
    void renderMenu();
    void renderSleepTrends();
    void processEvents();
    void update(float dt);
    void render();
    void updateView();
    static constexpr float WIDTH = 1200.f;
    static constexpr float HEIGHT = 1800.f;
    //HEAP MAP
    enum class DataMode{Map, Heap};
    DataMode mode = DataMode::Map;
    double loadMs = 0.0;
    sf::FloatRect mapHalf{{600.f,312.f}, {210.f,72.f}};
    sf::FloatRect heapHalf{{390.f,312.f}, {210.f,72.f}};
    sf:: Texture pillSelectTex{"assets/map_heap_chip.png"};
    void load_heap_data();
    void load_data();
    void drawModeSwitch();
    void drawPillLabel(const std:: string& text, sf::FloatRect half, bool selected);




    //TEXT INPUT BOX
    sf::FloatRect fromBox{{340.f, 1348.f}, {110.f, 60.f}};
    sf::FloatRect toBox{{520.f,1348.f}, {110.f,60.f}};
    std::string fromText;
    std::string toText;
    int focusedBox = 0;
    bool hasRange = false;
    const char* lastWho = "heap";
    int rangeLow=0;
    int rangeHigh=0;
    int rangeCount=0;
    double rangeMs=0.0;
    std::vector<float> rangeAverages;
    std::string rangeError;
    std::string& focusedText();
    void typeDigit(char32_t c);
    void rangeKey(sf::Keyboard::Key key);
    void applyRange();
    void drawInputBox(sf::FloatRect box, const std::string& text, bool focused);
   void drawRangePanel();





    //HOVER TEXT BOX
    int hoverLine=-1;
    int hoverDot=-1;
    sf::Vector2f hoverPos;
    sf::Texture tooltipTex{"assets/Info_square.png"};
    std::string formatValue(float v)const;
    void drawTooltip();
    //CHIPS
    sf::Texture chipTex[4]=
        {
        sf::Texture("assets/stress_chip.png"),
        sf::Texture("assets/caffeine_chip.png"),
        sf::Texture("assets/Screen_time_chip.png"),
        sf::Texture("assets/work_chip.png")
    };
    void drawChips();

    sf::Texture chipGlowTex{"assets/chip_glow.png"};
    std::vector<Button> chips;

    //Graph
    sf::FloatRect plotArea{{120.f, 447.f},{950.f,615.f}};
    float xForBuckect(int i) const;
    float yForValue(float val, float min_val,float max_val)const;
    void drawGraph(int line_index);

    void drawLine(sf::Vector2f a, sf:: Vector2f b, float thickness, sf::Color color);
    sf::Texture dot_glow;
    sf::Vector2f mouse_pos;

    sf::RenderWindow window;
    sf::RectangleShape box;
    sf::Texture bgTexture;//Menu Texture
    sf::Sprite bgSprite;

    sf::Texture Sleep_trend_texture;  //Sleep Trend screen
    sf::Sprite Sleep_trend_Sprite;
    //
    sf::Texture star1;           //STAR TEXTUREs
    sf::Sprite star1_sprite_;
    sf::Texture star2;
    sf::Sprite star2_sprite_;
    sf::Texture star3;
    sf::Sprite star3_sprite_;
    sf::Texture star4;
    sf::Sprite star4_sprite_;

    sf:: Texture z1; //ZZZ textures
    sf::Sprite z1_sprite;
    sf:: Texture z2;
    sf::Sprite z2_sprite;
    sf:: Texture z3;
    sf::Sprite z3_sprite;

    sf::Texture sleep_trend_button;   //Button Textures
    sf::Sprite sleep_trend_sprite;
    sf::Texture sleep_trend_glow;
    sf::Sprite sleep_glow_sprite;

    sf::Texture heap_button;   //Button Textures
    sf::Sprite heap_sprite;
    sf::Texture heap_glow;
    sf::Sprite heap_glow_sprite;

    Button heap_vs_button;
    Button sleep_trend_but;

    //Button template
    // sf::FloatRect Sleep_button_area{{185.f,1200.f}, {816.f,128.f}};
    // sf::FloatRect heap_button_area{{185.f,1400.f}, {816.f,128.f}};






    sf::Font font{"assets/Montserrat-Light.ttf"};
    sf:: Text clockText{font,"", 160};
    std:: string getTime_string();

    //UPDATE STARS
    float life_time=0.f;
    void drawStar(sf:: Sprite& s, float speed, float offset);



};