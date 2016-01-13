#include <iostream>
#include <SFML/Graphics.hpp> //loads up the SFML library

using namespace sf; //Use this so you don't have to type "sf::" in front of every SFML function
using namespace std;

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=600;

void process();

int main()
{
    //-----------------------------
    RenderWindow window; //creates the main window
    window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Works!"); //gives the main window attributes such as width, height, and a name
    //-----------------------------

    //-----------------------------
    window.setFramerateLimit(60);//sets frame rate (makes game speed faster/slower)
    //-----------------------------

    //-----------------------------
    RectangleShape mybox; //A rectangle shape
    mybox.setFillColor(Color::Red); //sets color
    mybox.setSize(Vector2f(20,30)/*an xy coordinate using float*/); //sets size
    mybox.setPosition(0,0); //sets position using the upper left corner of the box by default
    //-----------------------------


    //-----------------------------
    while (window.isOpen()) //the almighty gameloop (Keeps game running until gameover)
    {
        Event event; //creates an event, so we have access to it's many wonderful functions
        while (window.pollEvent(event))// event loop (constantly checks for user inputs and queues the actions)
        {
            switch (event.type)// checks the type of the event...
            {
            case Event::Closed: //closed event, triggered by clicking the X button
                window.close(); //closes the window
                break;

                // key pressed
            case Event::KeyPressed: //KeyPressed event, triggered by pressing any key
                switch (event.key.code) //takes in user inputs and performs actions
                {
                case Keyboard::Escape: //if esc button is pressed...
                    window.close();//close the window
                    break;

                case Keyboard::W://if W is pressed...
                    mybox.move(Vector2f(0,-5));//move the box up
                    break;

                case Keyboard::A://if A is pressed...
                    mybox.move(Vector2f(-5,0));//move the box left
                    break;

                case Keyboard::S://if S is pressed...
                    mybox.move(Vector2f(0,5));//move the box down
                    break;

                case Keyboard::D://if D is pressed...
                    mybox.move(Vector2f(5,0));//move the box right
                    break;

                default:
                    break;
                }//end of switch (event.key.code)
                break;

            default:
                break;
            }//end of switch (event.type)
        }//end of while (window.pollEvent(event))


        //~~~~~~~~~~~~~~~
        process();
        //~~~~~~~~~~~~~~~


        //~~~~~~~~~~~~~~~
        window.clear();//clears the screen
        window.draw(mybox);//draws your box shape on the screen (note: invisible unless displayed)
        //window.display();//displays what ever you drew.
        //~~~~~~~~~~~~~~~

    }//end of while (window.isOpen())

    //-----------------------------

}//end of int main()

void process()
{
    //Do your processing in here
}


