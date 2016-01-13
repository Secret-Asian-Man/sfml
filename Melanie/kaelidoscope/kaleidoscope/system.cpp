#include "system.h"
#include <game.h>
#include <triangle.h>

using namespace std;

/**********
 * MOVEMENT & BASICS
 **********/

void gameStuff(sf::RectangleShape& line, sf::RectangleShape &backCircle, sf::CircleShape& rotate, sf::CircleShape& view)
{
    line.setFillColor(sf::Color::White);  //just to clean up Game a little
    line.setSize(sf::Vector2f(1,600));
    line.setPosition(499,0);

    backCircle.setPosition(250,300);
    backCircle.setSize(sf::Vector2f(BOX_WIDTH,BOX_HEIGHT));
    backCircle.setOrigin(BOX_WIDTH/2,BOX_HEIGHT/2);
    backCircle.setFillColor(sf::Color::Transparent);
    backCircle.setOutlineColor(sf::Color::Cyan);
    backCircle.setOutlineThickness(1);

    rotate.setRadius(213);
    rotate.setOrigin(rotate.getRadius(),rotate.getRadius());
    rotate.setPosition(250,300);

    view.setPointCount(3);
    view.setRadius(100);
    view.setOrigin(view.getRadius(),view.getRadius());
    view.setPosition(250,300);
    view.setFillColor(sf::Color::Transparent);
    view.setOutlineColor(sf::Color::White);
    view.setOutlineThickness(2);
}

void setBorder(vector<sf::RectangleShape>& border) //so can use bounding boxes to keep view inside box
{
    for(int i=0;i<4;i++)
    {
        sf::RectangleShape line;
        border.push_back(line);
    }

    border[0].setSize(sf::Vector2f(BOX_WIDTH,1));
    border[0].setOrigin(BOX_WIDTH/2,1);
    border[0].setPosition(250,BOX_POSY-(BOX_HEIGHT/2));

    border[1].setSize(sf::Vector2f(BOX_WIDTH,1));
    border[1].setOrigin(BOX_WIDTH/2,1);
    border[1].setPosition(250,BOX_POSY+(BOX_HEIGHT/2));

    border[2].setSize(sf::Vector2f(1,BOX_HEIGHT));
    border[2].setOrigin(1,BOX_HEIGHT/2);
    border[2].setPosition(BOX_POSX-(BOX_WIDTH/2),300);

    border[3].setSize(sf::Vector2f(1,BOX_HEIGHT));
    border[3].setOrigin(1,BOX_HEIGHT/2);
    border[3].setPosition(BOX_POSX+(BOX_WIDTH/2),300);
}

void newArray(vector<triangle>& objects)
{
    if(objects.size()>0) //clears if array has anything in it (won't clear if first time creating)
    {
        objects.clear();
    }

    for(int i=0;i<151;i++)  //create array of i-1 objects (boxes/objects)
    {
        triangle object;
        objects.push_back(object);
    }
}

void presetArrays(vector<sf::CircleShape>& row,vector<sf::RectangleShape>& final)
{
    for(int i=0;i<8;i++) //create & position reflection tringles (make up third texture)
    {
        sf::CircleShape reflection;
        reflection.setPointCount(3);
        reflection.setRadius(80);
        reflection.setOrigin(reflection.getRadius(),reflection.getRadius());
        row.push_back(reflection);
        setRow(row,i);
    }

    for(int i=0;i<6;i++) //create & position rectangles that will be drawn
    {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(500,120));
        rectangle.setOrigin(rectangle.getSize().x/2,rectangle.getSize().y/2);
        final.push_back(rectangle);
        setRow(final,i);
    }
}

void setRow(vector<sf::CircleShape>& reflect, int i)
{
    switch(i%6)  //there's a pattern to the reflections
    {               //the only diffrence between the same types is location
    case 0:reflect[i].setScale(1,-1);
        reflect[i].setPosition((69.5*(i)),40.5);
        break;
    case 1:reflect[i].setScale(-1,-1);
        reflect[i].setPosition(69.5*i,80);
        reflect[i].setRotation(60);
        break;
    case 2:reflect[i].setScale(-1,1);
        reflect[i].setPosition(69.5*i,40.5);
        reflect[i].setRotation(60);
        break;
    case 3:reflect[i].setPosition(69.5*i,80);
        break;
    case 4:reflect[i].setScale(-1,1);
        reflect[i].setPosition(69.5*i,40.5);
        reflect[i].setRotation(-60);
        break;
    case 5:reflect[i].setScale(-1,-1);
        reflect[i].setPosition(69.5*i,80);
        reflect[i].setRotation(-60);
        break;
    }
}

void setRow(vector<sf::RectangleShape> &final, int i)
{
    switch(i%2)  //every other one is upside down
    {           //again changing location, but no pattern they just fill the screen
    case 0:final[i].setPosition(250,60+(118*i));
        final[i].setScale(1,-1);
        break;
    case 1:final[i].setPosition(250,60+(118*i));//178
        break;
    }
}

void moveView(sf::CircleShape& view, sf::CircleShape& rotate, vector<sf::RectangleShape> border, int X, int Y)
{
    int intersect=false;
    view.move(X,Y);       //move to check if going to be out of bounds
    rotate.move(-X,-Y);
    for(size_t i=0; i<border.size();i++)
    {
        intersect=collision(border[i],view); //checking here
        if(intersect==true)
        {
            i=border.size();
            view.move(-X,-Y);    //if they are out of bounds, move it back
            rotate.move(X,Y);
        }
    }
}

void moveView(sf::CircleShape &view, sf::CircleShape &rotate, vector<sf::RectangleShape> border)
{
    //check where view is moving to and if it hits a border bounce it back
}

bool collision(sf::RectangleShape border,sf::CircleShape view)
{
    sf::FloatRect boundBox=border.getGlobalBounds();
    sf::Vector2f point;
    bool intersect=false;

    for(int i=0;i<4;i++)  //looks at all sides of view
    {
        switch(i)  //bounding box wouldn't have worked b/c the way it shapes stuff
        {
        case 0:point.x=view.getPosition().x;
            point.y=view.getPosition().y-view.getRadius();
            break;
        case 1:point.x=view.getPosition().x+view.getRadius();
            point.y=view.getPosition().y;
            break;
        case 2:point.x=view.getPosition().x;
            point.y=view.getPosition().y+view.getRadius();
            break;
        case 3:point.x=view.getPosition().x-view.getRadius();
            point.y=view.getPosition().y;
            break;
        }

        if(boundBox.contains(point))
        {
            intersect=true;
            i=4;
        }
    }

    return(intersect);
}

void commands(sf::CircleShape &view, sf::CircleShape& rotate, vector<sf::RectangleShape> border)
{
    //controls
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) //rotate clockwise
    {
        rotate.rotate(-1);
        view.rotate(1);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //rotate counterclock
    {
        rotate.rotate(1);
        view.rotate(-1);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //move up
    {
        moveView(view,rotate,border,0,-1);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //move down
    {
        moveView(view,rotate,border,0,1);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //move left
    {
        moveView(view,rotate,border,-1,0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //move right
    {
        moveView(view,rotate,border,1,0);
    }

}

/**********************
 * DRAW & RENDER FUNCTS.
 **********************/

void drawObjs(vector<triangle> objects, sf::RenderWindow &window) //draws all boxes
{
    for(size_t i=0;i<objects.size();i++)
    {
        window.draw(objects[i].getShape());
    }
}

void drawObjs(vector<sf::RectangleShape> final,sf::RenderWindow& window) //draws textured boxes
{                                                                       //on right side of screen
    for(size_t i=0;i<final.size();i++)
    {
        window.draw(final[i]);
    }
}

void drawText(vector<triangle> objects, sf::RenderTexture &triTexture) //draw boxes on texture
{                                                                   //gets put on rotate circle
    triTexture.clear(sf::Color::Transparent);

    for(size_t i=0;i<objects.size();i++)
    {
        triTexture.draw(objects[i].getShape());
    }

    triTexture.display();
    triTexture.setSmooth(true);
}

void drawText(vector<sf::CircleShape>& row, sf::RenderTexture& sqrTexture)
{
    sqrTexture.clear(sf::Color::Transparent);

    for(size_t i=0;i<row.size();i++)    //draw rotate on row of triangles
    {
        sqrTexture.draw(row[i]);
    }

    sqrTexture.display();
    sqrTexture.setSmooth(true);
}

void setText(vector<sf::CircleShape>& row,sf::RenderTexture& triTexture)
{
    for(size_t i=0;i<row.size();i++) //set row textures as triTexture
    {
        row[i].setTexture(&triTexture.getTexture());
        row[i].setTextureRect(sf::IntRect(160,200,180,160));
    }

}

void setText(vector<sf::RectangleShape>& final,sf::RenderTexture& sqrTexture)
{
    for(size_t i=0;i<final.size();i++) //set all final textures as sqrTexture
    {
        final[i].setTexture(&sqrTexture.getTexture());
        final[i].setTextureRect(sf::IntRect(0,0,500,120));
    }

}



