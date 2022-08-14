#include "game.h"
#include "object.h"

#include <stdio.h>

// defining the global variables cuz weird c/c++ stuffs

std::vector<Object *> Game::objects;
double Game::ticks;
double Game::elapsed;

/**
 * @brief Calls update on all the active Objects with elapsed as the delta time
 * 
 * @param elapsed 
 */
void Game::update(double elapsed)
{
    Game::elapsed = elapsed;
    Game::ticks += elapsed;

    for (Object *object : Game::objects)
    {
        object->update(elapsed);
    }
}

/**
 * @brief Calls render on all the active Objects
 * 
 */
void Game::render()
{
    Game::window.clear();

    for (Object *object : Game::objects)
    {
        object->render();
    }

    Game::window.display();
}