#include "triangle.h"
#include <iostream>

using namespace std;

triangle::triangle()
{
    object.setSize(sf::Vector2f((rand()%(40-20))+20,(rand()%(40-20))+20));
    object.setOrigin(object.getSize().x/2,object.getSize().y/2);
    object.setPosition((rand()%(((250+350/2)-(40/2))-((250-350/2)+(40/2))))+((250-350/2)+(40/2))
                       ,(rand()%(((300+350/2)-(40/2))-((300-350/2)+(40/2))))+((300-350/2)+(40/2)));

    int color;
    color=rand()%6;

    switch(color) //random color
    {
    case 0: object.setFillColor(sf::Color::Blue);
        break;
    case 1: object.setFillColor(sf::Color::Green);
        break;
    case 2: object.setFillColor(sf::Color::Cyan);
        break;
    case 3: object.setFillColor(sf::Color::Yellow);
        break;
    case 4: object.setFillColor(sf::Color::Magenta);
        break;
    case 5: object.setFillColor(sf::Color::Red);
        break;
    }
}

sf::RectangleShape triangle::getShape() //class stuff
{
    return(object);
}

void triangle::Move(double X, double Y)
{
    object.move(X,Y);
}

double triangle::getPosX()
{
    double X;

    X=object.getPosition().x;

    return(X);
}

double triangle::getPosY()
{
    double Y;

    Y=object.getPosition().y;

    return(Y);
}

double triangle::getHeight()
{
    double height;

    height=object.getSize().y;

    return(height);
}

double triangle::getWidth()
{
    double width;

    width=object.getSize().x;

    return(width);
}

void triangle::setPosition(double X, double Y)
{
    object.setPosition(X,Y);
}
