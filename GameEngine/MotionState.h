#ifndef MOTIONSTATE_H
#define MOTIONSTATE_H

#include <btBulletDynamicsCommon.h>
#include <bullet\BulletDynamics\Dynamics\btRigidBody.h>


class MotionState : public btMotionState {
public:
	MotionState(const btTransform& initialPosition) {
		mInitialPosition = initialPosition;
	}
	virtual void getWorldTransform(btTransform& worldTrans) const {
		worldTrans = mInitialPosition;
	}

private:
	btTransform mInitialPosition;
};

#endif MOTIONSTATE_H