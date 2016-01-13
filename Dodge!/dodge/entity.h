#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <sfml/Audio.hpp>

enum DIRECTION{UP,DOWN,LEFT,RIGHT};

class entity
{
public:
    //Constructors
    entity();


    //Destructor
    ~entity();


    //Accessors


    //Mutators


    //Operators


    //Functions
    void move(DIRECTION whichWay);
    void selfDestruct();
    bool isCollide();


protected:

    //Private Member Variables
    sf::Shape body;

    //Private Functions




};

#endif // ENTITY_H
