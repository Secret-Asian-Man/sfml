#include <iostream>
#include "game.h"


using namespace std;

int main()
{
    try
    {
        game start;
    }
    catch(GAME_ERRORS error)
    {
        switch (error)
        {
        case ERROR:
            std::cout<<"ERROR ERROR "<<std::endl;
            break;

        default:
            std::cout<<"Unknown Error... "<<std::endl;
            break;
        }
    }











    return 0;
}

