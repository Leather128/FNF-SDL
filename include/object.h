#pragma once

/**
 * @brief Basic class for other objects in the game to extend.
 *
 */
class Object
{
public:
    // class functions (contructor and destructor)
    Object();
    virtual ~Object() = default;
    void Delete();
    // basic functions of all game objects
    virtual void update(double elapsed);
    virtual void render();
};