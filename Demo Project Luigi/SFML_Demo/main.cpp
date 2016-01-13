#include <iostream>
#include <SFML/Graphics.hpp>
#include <sfml/Audio.hpp>
#include <vector>

//sound
//music
//textures
//mouse tracking
//view
//CLOCK
//COLLISION
//SPRITES


//render texture
//text
//drawing with vertex arrays

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=600;
const int AMOUNT_OF_SOUND_EFFECTS=2;
const double TIME=100; //used for the Clock (in miliseconds)


using namespace std;
using namespace sf;

void process(const RenderWindow &window,const Mouse &mouse, RectangleShape &myBox);
void animate(Clock &clock, Time &time, Sprite &sprite, int speed, int &left, int &top, int width, int height, int frames, bool &toggle);




int main()
{


    std::cout<<"DEBUG : "<<std::endl;
    //-----------------------------
    //ANIMATION VARIABLES

    //declared variables here to use in the animate() function later
    int left=0; //x coordinate of sprite
    int top=0; //y coordinate of sprite
    int width=32; //how many pixels wide the sprite is
    int height=74;//how many pixels tall the sprite is
    int frames=5; //number of frames the sprite has. 0 based! 6 frames total
    bool toggle=true;//used to play the sprite in forward and reverse
    //-----------------------------

    //-----------------------------
    //WINDOW

    RenderWindow window; //creates the main window
    window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Works!"); //gives the main window attributes such as width, height, and a name
    //-----------------------------


    //-----------------------------
    //FRAMERATE

    window.setFramerateLimit(60);//sets frame rate (makes game speed faster/slower)
    //-----------------------------


    //-----------------------------
    //EVENT

    Event event; //allows you to get input from the keyboard/joystick
    //-----------------------------


    //-----------------------------
    //MOUSE

    Mouse mouse; //allows you to get input from the mouse
    //-----------------------------

    //-----------------------------
    //CAMERA

    View view(FloatRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT));// FloatRect(x,y,object width,object height) (the object is my window)
    view.setCenter(Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2)); //sets center to the middle of the window
    //WARNING: remember to use "window.setView(view);" just before window.display();

    //-----------------------------

    //-----------------------------
    //CLOCK

    Clock clock; //starts counting in seconds, miliseconds, or microseconds starting now!
    Time time; //able to store the current count from the clock in seconds, miliseconds, or microseconds
    //-----------------------------


    //-----------------------------
    //BOX

    RectangleShape mybox; //A rectangle shape
    mybox.setFillColor(Color::Green); //sets color
    mybox.setSize(Vector2f(32,74)/*an xy coordinate using float*/); //sets size
    mybox.setPosition(0,0); //sets position using the upper left corner of the box by default
    //-----------------------------


    //-----------------------------
    //SOUND EFFECTS (Note: keep in mind supported files, .mp3 is NOT supported)

    //AMOUNT_OF_SOUND_EFFECTS=2 for this demo
    SoundBuffer buffer[AMOUNT_OF_SOUND_EFFECTS]; //a SoundBuffer preloads a sound, aka gets it ready for use. Here we have an array of them for multiple sound effects.
    Sound sound[AMOUNT_OF_SOUND_EFFECTS]; //a Sound is given a SoundBuffer so it may be played. Here we have an array of them for multiple sound effects.
    string soundEffectName[AMOUNT_OF_SOUND_EFFECTS]={"lm_coin.wav","okeedokee.wav"};//SoundBuffers need the name of the file, to look for it. (PUT ALL FILES IN BUILD FOLDER)

    for (int i=0;i<AMOUNT_OF_SOUND_EFFECTS;i++)
    {
        if (!buffer[i].loadFromFile(soundEffectName[i])) //ie: load the 1st SoundBuffer using the 1st soundEffectName into the 1st sound
            cout<<"File failed to load!!!"<<endl;
        sound[i].setBuffer(buffer[i]);
    }
    //-----------------------------


    //-----------------------------
    //MUSIC (Note: keep in mind supported files, .mp3 is NOT supported)

    Music music; //Music is not preloaded, but rather streamed from the file itself.

    if (!music.openFromFile("Super Mario 64 Soundtrack - Super Mario 64 (Main Theme) (256kbit).wav")) //opens the file (note: doesn't "loadFromFile" since streaming)  (PUT ALL FILES IN BUILD FOLDER)
    {
        cout<<"File failed to load!!!"<<endl;
    }

    music.play(); //plays the music
    music.setLoop(true); //music will now play again when over.
    music.setVolume(30); //volume from 0-100
    //-----------------------------


    //-----------------------------
    //BACKGROUND (Note: keep in mind supported files, .png is recommended)

    Texture backgroundTexture; //a Texture preloads the image, aka gets it ready to be used.
    if (!backgroundTexture.loadFromFile("mario2s1.gif")) //loads file into texture (PUT ALL FILES IN BUILD FOLDER)
    {
        cout<<"File failed to load!!!"<<endl;
    }

    Sprite backgroundSprite; //sprites allows the image to be shown and manipulated (remember to draw this sprite using "window.draw(backgroundSprite)")
    backgroundSprite.setTexture(backgroundTexture); //passed image data from texture to sprite
    backgroundSprite.setScale(sf::Vector2f(0.5,0.5)); //shrank the original image by half
    //-----------------------------


    //-----------------------------
    // LUIGI SPRITE (Note: keep in mind supported files, .png is recommended)

    Texture luigiDanceTexture;//a Texture preloads the image, aka gets it ready to be used.
    if (!luigiDanceTexture.loadFromFile("LuigiDanceSpriteSheet.png")) //loads file into texture (PUT ALL FILES IN BUILD FOLDER)
    {
        cout<<"File failed to load!!!"<<endl;
    }

    Sprite luigiDanceSprite;//sprites allows the image to be shown and manipulated (remember to draw this sprite using "window.draw(luigiDanceSprite)")
    luigiDanceSprite.setTexture(luigiDanceTexture);//passed image data from texture to sprite
    luigiDanceSprite.setPosition(310,468); //moved sprite to a spot I liked.

    //-----------------------------


    //-----------------------------

    while (window.isOpen())//GAME LOOP
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

                case Keyboard::P:
                    if (music.getStatus()==2) //0=stopped, 1=paused, 2=play
                    {
                        music.pause(); //pauses the music
                    }
                    else
                        music.play(); //resumes music
                    break;

                case Keyboard::Z:
                    sound[0].play(); //plays the sound effect in slot 0 (currently the coin sound)
                    break;

                case Keyboard::X:
                    sound[1].play(); //plays the sound effect in slot 1 (currently the okeedokee sound)
                    break;

                case Keyboard::Add:
                    view.zoom(0.9); //zooms in
                    break;

                case Keyboard::Subtract:
                    view.zoom(1.1); //zooms out
                    break;

                case Keyboard::Left:
                    view.move(Vector2f(-5,0));//moves the camera Left
                    break;

                case Keyboard::Right:
                    view.move(Vector2f(5,0));//moves the camera Right
                    break;

                case Keyboard::Up:
                    view.move(Vector2f(0,-5));//moves the camera Up
                    break;

                case Keyboard::Down:
                    view.move(Vector2f(0,5));//moves the camera Down
                    break;


                case Keyboard::A:
                    luigiDanceSprite.move(-10,0);//moves luigi left
                    break;

                case Keyboard::D:
                    luigiDanceSprite.move(10,0);//moves luigi right
                    break;

                case Keyboard::W:
                    luigiDanceSprite.rotate(10);//rotates luigi clockwise
                    break;

                case Keyboard::S:
                    luigiDanceSprite.rotate(-10);//rotates luigi anticlockwise
                    break;

                default:
                    break;

                }//end of switch (event.key.code)

            }// end of else if (event.type==Event::KeyPressed)

        }//end of while (window.pollEvent(event))


        process(window, mouse, mybox);


        animate(clock,time,luigiDanceSprite,TIME,left,top,width,height,frames, toggle);

        //view.setCenter(Vector2f(mouse.getPosition().x, mouse.getPosition().y)); //sets camera to mouse
        //luigiDanceSprite.setPosition(mouse.getPosition(window).x,mouse.getPosition(window).y); //attachs luigi to mouse

        window.clear(); //clears teh screen
        window.draw(backgroundSprite); //draws the background
        window.draw(mybox); //draws the box
        window.draw(luigiDanceSprite); //draws luigi
        window.setView(view); //positions the camera
        window.display(); //displays everything drawn
        //system("cls"); //clears the cmd prompt screen

    }// end of while (window.isOpen())

    //-----------------------------


}//end of int main()

//in this case im using the process() function to get the box to follow my mouse, and collide with the window.
void process(const RenderWindow &window, const Mouse &mouse, RectangleShape &myBox)
{
    cout<<"("<<mouse.getPosition(window).x<<","<<mouse.getPosition(window).y<<")"<<endl; //outputs current mouse coordinate


    //-----------------------------
    //COLLISION

    //Very complicated I know, just take it one side at a time plus a default.



    //mouse.getPosition(window) is given the parameter "window" to get mouse coordinates of the game window, instead of your computer screen
    if (mouse.getPosition(window).x<=0) //left side of window
    {
        myBox.setFillColor(Color::Red);
        myBox.setPosition(0,myBox.getPosition().y); //moves the box back to the left edge of the window
    }




    else if(mouse.getPosition(window).y<=0) //top side window
    {
        myBox.setFillColor(Color::Red);
        myBox.setPosition(myBox.getPosition().x,0); //moves the box back to the top edge of the window
    }



    //myBox.getGlobalBounds() is how many pixels tall or wide the box is
    else if(mouse.getPosition(window).x>=SCREEN_WIDTH-myBox.getGlobalBounds().width) //right side of window
    {
        myBox.setFillColor(Color::Red);
        myBox.setPosition(SCREEN_WIDTH-myBox.getGlobalBounds().width, myBox.getPosition().y); //moves the box back to the right edge of the window
    }




    else if(mouse.getPosition(window).y>=SCREEN_HEIGHT-myBox.getGlobalBounds().height) //bottom side of window
    {
        myBox.setFillColor(Color::Red);
        myBox.setPosition(myBox.getPosition().x, SCREEN_HEIGHT-myBox.getGlobalBounds().height);//moves the box back to the bottom edge of the window
    }




    else //default
    {
        myBox.setPosition(mouse.getPosition(window).x,mouse.getPosition(window).y);//sets box to current mouse position
        myBox.setFillColor(Color::Green);
    }
    //-----------------------------
}








void animate(Clock &clock, Time &time, Sprite &sprite,int speed, int &left, int &top, int width, int height, int frames, bool &toggle)
{
    time=clock.getElapsedTime(); //sets the time variable to the elapsed time, given by clock.

    if (time.asMilliseconds()>=speed-time.asMilliseconds()) //every [TIME] seconds do your thing while accounting for lag
    {
        cout<<"DEBUG time: "<<time.asMilliseconds()<<" Lag: "<<time.asMilliseconds()-(speed-time.asMilliseconds())<<endl; //displays total time, and amount of lag




        if (toggle==true)//go forward 1 frame
        {
            left=left+width;
        }

        if (toggle==false)//go back 1 frame
        {
            left=left-width;
        }

        if (left<=0 || left>=(width*frames))//toggle when at first or last frame
        {
            toggle=!toggle;
        }

        sprite.setTextureRect(IntRect(left,top,width,height)); //Sets the sprite to the indicated frame. IntRect(X-coord of sprite, Y-coord of sprite, width of sprite in pixels, height of sprite in pixels)

        clock.restart(); //restart the clock
    }
}
