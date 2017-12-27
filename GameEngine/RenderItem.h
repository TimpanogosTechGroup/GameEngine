#pragma once

class RenderItem {
public:
	unsigned int &GetID() { return id; };
	void SetId(unsigned int ID) { id = ID; };

private:
	unsigned int id;
};