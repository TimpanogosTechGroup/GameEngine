#include "PrimitiveShape.h"

Object* PrimitiveShape::GenerateSquare(float width, float height, Material material) {
	Object* object = new Object;

	// First Triangle
	object->GetVerticies().AddFloat(0)->AddFloat(0)->AddFloat(0);// First vertex
	object->GetVerticies().AddFloat(width)->AddFloat(0)->AddFloat(0);// Second vertex
	object->GetVerticies().AddFloat(width)->AddFloat(height)->AddFloat(0);// Third vertex

	// Second triangle
	object->GetVerticies().AddFloat(0)->AddFloat(0)->AddFloat(0);// First vertex
	object->GetVerticies().AddFloat(width)->AddFloat(height)->AddFloat(0);// Third vertex
	object->GetVerticies().AddFloat(0)->AddFloat(height)->AddFloat(0);// Fourth vertex

	object->SetMaterial(material);

	object->GetVerticies().ToString();

	return object;
}