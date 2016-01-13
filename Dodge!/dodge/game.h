#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <sfml/Audio.hpp>
#include <vector>
#include "player.h"
#include "enemy.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

using std::vector;

enum GAME_ERRORS{ERROR};

using namespace sf;
class game
{
public:
    //Constructors
    game();


    //Destructor
    ~game();


    //Accessors


    //Mutators


    //Operators


    //Functions


private:
    //Private Member Variables
    RenderWindow window;
    Mouse mouse;
    Event event;
    Clock clock;
    Time time;


    player me;
    vector<enemy> enemies;

    //Private Functions
    void gameLoop();
    void eventLoop();
    void process();

};

#endif // GAME_H
