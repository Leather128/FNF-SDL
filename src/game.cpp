#include "game.h"
#include "object.h"

// defining the global variables cuz weird c/c++ stuffs

std::vector<Object *> Game::objects;
double Game::ticks;
double Game::elapsed;
const Uint8 *Game::keyboard_state;

void Game::init()
{
    Game::keyboard_state = SDL_GetKeyboardState(NULL);
}

void Game::update(double elapsed)
{
    Game::elapsed = elapsed;
    Game::ticks += elapsed;

    for (Object *object : Game::objects)
    {
        object->update(elapsed);
    }
}

void Game::render()
{
    Game::window.clear();

    for (Object *object : Game::objects)
    {
        object->render();
    }

    Game::window.display();
}