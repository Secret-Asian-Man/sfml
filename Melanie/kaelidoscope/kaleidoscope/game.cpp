#include "game.h"
#include "constants.h"
#include <iostream>
#include <vector>
#include <system.h>
#include <triangle.h>

using namespace std;

Game::Game()
{
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Kaleidoscope");
    window.setFramerateLimit(60);

    srand(time(0));  //seed rand num generator

    triTexture.create(500,600);  //create texture
    if(!triTexture.create(500,600))
    {
        cout<<"nope"<<endl;
    }

    sqrTexture.create(500,600);
    if(!sqrTexture.create(500,600))
    {
        cout<<"Nope."<<endl;
    }

    rotation.create(500,600);
    if(!rotation.create(500,600))
    {
        cout<<"NOPE!"<<endl;
    }

    gameStuff(line,backCircle,rotate,view); //set all positions & etc for shapes & stuff

    Left.setCenter(250,300);  //setting up views (how do the splitscreen)
    Left.setSize(500,600);
    Left.setViewport(sf::FloatRect(0,0,0.5,1));

    Right.setCenter(250,300);
    Right.setSize(500,600);
    Right.setViewport(sf::FloatRect(0.5,0,0.5,1));

    demo=false;
}

void Game::run()
{
    vector<triangle> objects;
    vector<sf::CircleShape> row;
    vector<sf::RectangleShape> final;

    setBorder(border);
    newArray(objects); //random rectangles
    presetArrays(row,final);//set points & pos for texture setup

   while (window.isOpen()) //run game
   {
       processEvents(objects);
       update(objects,row,final);
       render(objects,final); //clear/draw/display
   }
}

/******************
 * IN RUN
 ******************/

void Game::processEvents(vector<triangle>& objects)
{
   sf::Event event;
   while (window.pollEvent(event))
   {
       switch (event.type)
       {
       case sf::Event::Closed:
           window.close();
           break;

       // key pressed
       case sf::Event::KeyPressed: //wish I could make this a switch statement... maybe I can, but I didn't see how

           if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
           {
               if(demo==false)
               {
                   demo=true;
               }

               else
               {
                   demo=false;
               }

               //cout<<"demo: "<<demo<<endl;
           }

           if(demo==false)
           {
               commands(view,rotate,border); //all the rotation and movement commands
           }

           if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) //reset view rotation and position
           {
               rotate.setPosition(250,300);
               rotate.setRotation(0);
               view.setPosition(250,300);
               view.setRotation(0);
           }

           if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //new triangles
           {
               newArray(objects);
           }
           break;
        default:
               break;
       }
   }
}

void Game::update(vector<triangle>& objects, vector<sf::CircleShape> &row, vector<sf::RectangleShape> &final)
{
    //commands here again lets stuff move smoothly
    //also moves stuff while demo mode is on
    if(demo==false)
    {
        commands(view,rotate,border);
    }

    else
    {
        rotate.rotate(-1.5);
        view.rotate(1.5);
        moveView(view,rotate,border);
    }

    //update textures
    drawText(objects,rotation); //draw all objects on rotation

    rotate.setTexture(&rotation.getTexture()); //put rotation texture onto object to rotate
    rotate.setTextureRect(sf::IntRect(37,87,426,426));

    triTexture.clear(sf::Color::Transparent);
    triTexture.draw(rotate);   //draw rotating object onto texture for triangles
    triTexture.display();
    triTexture.setSmooth(true); //only put stuff w/ arrays in another function

    setText(row,triTexture);//set row textures as triTexture

    drawText(row,sqrTexture); //draw row on sqrTexture
    setText(final,sqrTexture);//set all final textures as sqrTexture
}

void Game::render(vector<triangle> objects, vector<sf::RectangleShape> final)
{
       window.clear();
       Draw(objects,final);
       window.display();
}

/*****************
 * IN RENDER
 *******************/

void Game::Draw(vector<triangle> objects, vector<sf::RectangleShape> final)
{
    window.setView(Left); //draw left side of screen
    drawObjs(objects,window);
    window.draw(backCircle);
    window.draw(view);
    window.draw(line);
    //window.draw(rotate);

    window.setView(Right); //draw right side of screen
    drawObjs(final,window);
}

