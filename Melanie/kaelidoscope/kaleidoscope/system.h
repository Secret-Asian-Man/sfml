#ifndef SYSTEM_H
#define SYSTEM_H
#include <constants.h>

#include <vector>
#include <triangle.h>
#include <game.h>
#include <iostream>

using namespace std;
    //movement & basics
    void gameStuff(sf::RectangleShape& line, sf::RectangleShape& backCircle, sf::CircleShape &rotate, sf::CircleShape& view);
    void setBorder(vector<sf::RectangleShape>& border);
    void newArray(vector<triangle>& objects);
    void presetArrays(vector<sf::CircleShape>& row,vector<sf::RectangleShape>& final);
    void setRow(vector<sf::CircleShape>& reflect, int i);
    void setRow(vector<sf::RectangleShape> &final, int i);
    void moveView(sf::CircleShape& view, sf::CircleShape& rotate, vector<sf::RectangleShape> border, int X, int Y);
    void moveView(sf::CircleShape &view, sf::CircleShape &rotate, vector<sf::RectangleShape> border);
    bool collision(sf::RectangleShape border,sf::CircleShape view);
    void commands(sf::CircleShape& view, sf::CircleShape& rotate, vector<sf::RectangleShape> border);

    //drawing & rendering (textures)
    void drawObjs(vector<triangle> objects,sf::RenderWindow& window);
    void drawObjs(vector<sf::RectangleShape> final,sf::RenderWindow& window);
    void drawText(vector<triangle> objects,sf::RenderTexture& triTexture);
    void drawText(vector<sf::CircleShape>& row,sf::RenderTexture& sqrTexture);
    void setText(vector<sf::CircleShape>& row,sf::RenderTexture& triTexture);
    void setText(vector<sf::RectangleShape>& final,sf::RenderTexture& sqrTexture);

#endif // SYSTEM_H
