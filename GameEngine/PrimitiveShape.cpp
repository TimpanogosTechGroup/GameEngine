#include "PrimitiveShape.h"

Object* PrimitiveShape::GenerateSquare(float width, float height) {
	Object* object = new Object;
	object->GetVerticies().AddFloat(0)->AddFloat(0)->AddFloat(0);// First vertex
	object->GetVerticies().AddFloat(width)->AddFloat(0)->AddFloat(0);// Second vertex
	object->GetVerticies().AddFloat(width)->AddFloat(height)->AddFloat(0);// Third vertex
	object->GetVerticies().AddFloat(0)->AddFloat(height)->AddFloat(0);// Fourth vertex

	object->GetVerticies().ToString();

	return object;
}