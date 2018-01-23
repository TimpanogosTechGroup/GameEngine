#pragma once

#include <btBulletDynamicsCommon.h>
#include <BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h>
#include "RegistryEntry.h"

class PhysicsEngine : public RegistryEntry {
public:
	void PhysicsTest();
};