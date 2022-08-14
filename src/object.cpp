#include <stdio.h>
#include <algorithm>

#include "object.h"
#include "game.h"

/**
 * @brief Construct a new blank Object:: Object object
 * 
 */
Object::Object()
{
    // Object is a template class to base others off of,
    // thus nothing happens in any of these basic functions.
    // (Besides being freed from memory)
}

/**
 * @brief Delete the Object:: Object from memory (and from the game object list if found).
 * 
 */
void Object::Delete()
{
    if(std::find(Game::objects.begin(), Game::objects.end(), this) != Game::objects.end())
        Game::objects.erase(std::find(Game::objects.begin(), Game::objects.end(), this));

    delete this;
}

/**
 * @brief Do nothing.
 * 
 * @param elapsed 
 */
void Object::update(double elapsed) {}

/**
 * @brief Do nothing.
 * 
 */
void Object::render() {}