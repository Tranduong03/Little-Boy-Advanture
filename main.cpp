#include <iostream>
#include "SDL.h"    
#include "Engine.h"


int main(int argc, char* argv[])
{
    int cur_status = 0;

    Engine::GetInstance()->Init("Little Boy Advanture",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, 0);

    do {
        if (cur_status != 2) Engine::GetInstance()->Menu();
        else
        {
            int check = Engine::GetInstance()->BeforePlay();
            if (check == -1) Engine::GetInstance()->Menu();
        }
        while (Engine::GetInstance()->running()) {
            Engine::GetInstance()->update();
            Engine::GetInstance()->render();
        }

    } while (cur_status != 0);
    Engine::GetInstance()->clean();
    return 0;
}
