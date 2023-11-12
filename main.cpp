#include <iostream>
#include "SDL.h"    
#include "Engine.h"



int main(int argc, char* argv[])
{
    int cur_status = 1;

    Engine::GetInstance()->Init("Little Boy Advanture",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, 0);

    do {
        Engine::GetInstance()->restart();
        cout << "Trang thai hien tai:" << cur_status << endl;
        if (cur_status == 1) Engine::GetInstance()->Menu();
        else
        {
            int check = Engine::GetInstance()->BeforePlay();
        }

        while (Engine::GetInstance()->running()) {
            Engine::GetInstance()->handleEvents();
            Engine::GetInstance()->update();
            Engine::GetInstance()->render();
        }

        cur_status = Engine::GetInstance()->FinishGame();
    } while (cur_status != 0);
    Engine::GetInstance()->clean();
    return 0;
}