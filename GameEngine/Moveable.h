#ifndef MAOVABLE_H
#define MOVABLE_H

#include "Entity.h"

class Moveable : virtual public Entity {
public:
	// Notice how these are not virtual functions, these are defined here and can be overloaded
	void moveEntity() {}; // Moves the entity, calls the wolrd functions to move the entity in the World
	void rotateEntity() {}; // Rotates the entity, clss the world functions to rotate the entity in the World
private:
};

#endif