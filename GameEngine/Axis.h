#ifndef AXIS_H
#define AXIS_H

#include "RenderItem.h"

class Axis : public RenderItem {
public:
	enum AXIS_DIR { X_AXIS, Y_AXIS, Z_AXIS, XY_AXIS, XZ_AXIS, YZ_AXIS, AYZ_AXIS };
private:
	double mdegree;
	AXIS_DIR mAxisDir = X_AXIS;
public:
	Axis() {

	}
};

#endif