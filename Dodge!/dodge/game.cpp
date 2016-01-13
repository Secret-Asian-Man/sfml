#include "game.h"

game::game()
{
    RenderWindow window;
    Mouse mouse;
    Event event;
    Clock clock;
    Time time;

    window.create(VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"Dodge!");
    window.setFramerateLimit(60);

    gameLoop();

}

game::~game()
{

}

void game::gameLoop()
{
    while (window.isOpen())//GAME LOOP
    {

        eventLoop();

        //process

        window.clear();
        window.draw(/*something*/);
        window.display();
    }

}

void game::eventLoop()
{
    while (window.pollEvent(event)) //EVENT LOOP
    {
        if (event.type==Event::Closed)
        {
            window.close();
        }

        else if (event.type==Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case Keyboard::Escape:
                window.close();
                break;

            }//end of switch (event.key.code)

        }// end of else if (event.type==Event::KeyPressed)

    }//end of while (window.pollEvent(event))
}

void game::process()
{

}

