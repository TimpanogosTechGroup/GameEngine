#include "PrimitiveShape.h"

Object* PrimitiveShape::GenerateSquare(float width, float height, Material* material) {
	Object* object = new Object;

	// Ceate the vertex shape of the square

	// First Triangle
	object->GetVerticies().AddFloat(0)->AddFloat(0)->AddFloat(0);// First vertex
	object->GetVerticies().AddFloat(width)->AddFloat(0)->AddFloat(0);// Second vertex
	object->GetVerticies().AddFloat(width)->AddFloat(height)->AddFloat(0);// Third vertex

	// Second triangle
	object->GetVerticies().AddFloat(0)->AddFloat(0)->AddFloat(0);// First vertex
	object->GetVerticies().AddFloat(width)->AddFloat(height)->AddFloat(0);// Third vertex
	object->GetVerticies().AddFloat(0)->AddFloat(height)->AddFloat(0);// Fourth vertex

	// Add Texture coordinates

	object->GetUVCoords().AddFloat(0)->AddFloat(0)->AddFloat(1)->AddFloat(0)->AddFloat(1)->AddFloat(1);
	object->GetUVCoords().AddFloat(0)->AddFloat(0)->AddFloat(1)->AddFloat(1)->AddFloat(0)->AddFloat(1);

	// Add normals
	// First Triangle
	object->GetNormals().AddFloat(0)->AddFloat(0)->AddFloat(1);// First vertex
	object->GetNormals().AddFloat(0)->AddFloat(0)->AddFloat(1);// First vertex
	object->GetNormals().AddFloat(0)->AddFloat(0)->AddFloat(1);// First vertex
	object->GetNormals().AddFloat(0)->AddFloat(0)->AddFloat(1);// First vertex
	object->GetNormals().AddFloat(0)->AddFloat(0)->AddFloat(1);// First vertex
	object->GetNormals().AddFloat(0)->AddFloat(0)->AddFloat(1);// First vertex

	object->SetMaterial(material);

	object->GetVerticies().ToString();
	object->GetUVCoords().ToString();

	return object;
}