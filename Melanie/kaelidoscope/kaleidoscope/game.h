#ifndef GAME_H
#define GAME_H
#include <constants.h>

#include <SFML/Graphics.hpp>
#include <triangle.h>
#include <iostream>
#include <system.h>
#include <cmath>

using namespace std;

class Game{
public:
    friend class triangle;
    Game();
    void Draw(vector<triangle> objects, vector<sf::RectangleShape> final);
    void run();
    void processEvents(vector<triangle> &objects);
    void update(vector<triangle> &objects, vector<sf::CircleShape>& row, vector<sf::RectangleShape>& final);
    void render(vector<triangle> objects, vector<sf::RectangleShape> final);


private:
    sf::RenderWindow window;
    sf::RenderTexture triTexture;
    sf::RenderTexture sqrTexture;
    sf::RenderTexture rotation;
    sf::RectangleShape backCircle;
    sf::CircleShape rotate;
    sf::CircleShape view;
    sf::RectangleShape line;
    sf::View Left;
    sf::View Right;
    vector<sf::RectangleShape> border;
    bool demo;
};


#endif // GAME_H
