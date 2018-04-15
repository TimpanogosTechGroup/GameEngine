/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef DYNAMIC_ENTITY_H
#define DYNAMIC_ENTITY_H

#include "Moveable.h"

/*
Author: Ben Brenkman aka JustBremkman

Description:
This is the Physical layer to the entity, gives the entity the ability to move, determines if it is tangablea and mass 
All Entities have transformations, so there is no need to have them in this class
*/

class DynamicEntity : public virtual Moveable {
public:
	enum RIGIDBODY_TYPE { BOUNDING_BOX, SPHERE, CONVEX_HULL, COMPLEX_HULL, NONE };
private:
	double entity_mass = 0.0; // The mass of the entity in kilograms 
	//bool isTangable = true; // Enabled by default, makes the entity collidable with other objects. unlike a ghost.
	RIGIDBODY_TYPE mCollisionType = BOUNDING_BOX;
public:
	/*
	* Returns the mass of the entity, used for physics calculations
	*/
	double getMass() {
		return entity_mass;
	}
	/*
	* Sets the mass of the entity, used for physics calculations
	*/
	void setMass(double mass) {
		entity_mass = mass;
	};
	/*
	* Sets the collison type of the dynamic body.
	*/
	void setCollisionType(RIGIDBODY_TYPE type) {
		mCollisionType = type;
	}
};

#endif