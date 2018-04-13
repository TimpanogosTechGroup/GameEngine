#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Entity.h"

/*
* Author: Ben Brenknan aka JustBrenkman
* Description: This is a renderable extension of the entity allows entities to be rnedered
* Calls the world renderer and renderrs the entity
*/

class Renderable : public virtual Entity {
private:
	//Render profile goes here
public:
	virtual void render() = 0; // function called when the game wants to render and entity
};

#endif