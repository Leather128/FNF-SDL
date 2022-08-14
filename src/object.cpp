#include <stdio.h>
#include <algorithm>

#include "object.h"
#include "game.h"

Object::Object()
{
    // Object is a template class to base others off of,
    // thus nothing happens in any of these basic functions.
    // (Besides being freed from memory)
}

void Object::Delete()
{
    if(std::find(Game::objects.begin(), Game::objects.end(), this) != Game::objects.end())
        Game::objects.erase(std::find(Game::objects.begin(), Game::objects.end(), this));

    delete this;
}

void Object::update(double elapsed) {}
void Object::render() {}