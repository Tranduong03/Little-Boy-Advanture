#include <iostream>
#include <SDL.h>
#include "Engine.h"


int main(int argc, char* argv[]) 
{
    int cur_status = 0;

   
    Engine::GetInstance()->Init("Little Boy Advanture", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, 0);
    do {
        Engine::GetInstance()->Menu();
    } while (cur_status == 0);
    Engine::GetInstance()->clean();


    return 0;
}