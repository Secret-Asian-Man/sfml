#ifndef OBJECT_H
#define OBJECT_H
#include <constants.h>

#include <SFML/Graphics.hpp>
#include <cmath>

class triangle  //would be better if called rectangle but I don't want to have to rename EVERYTHING
{               //kept as class to make it easier to randomize little boxes
public:
    friend class game;
    triangle();
    sf::RectangleShape getShape();
    void setVeloc(int X, int Y);
    void Move(double X,double Y);
    void setPosition(double X, double Y);
    double getPosX();
    double getPosY();
    double getHeight();
    double getWidth();


private:
    sf::RectangleShape object;
};

#endif // OBJECT_H
