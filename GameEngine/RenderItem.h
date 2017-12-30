#pragma once

// All things that are managed by opengl have an ID, so this class keeps that nicely handled.
class RenderItem {
public:
	unsigned int &GetID() { return id; };
	void SetId(unsigned int ID) { id = ID; };
	unsigned int &GetIDVAO() { return id_VAO; };
	void SetIdVAO(unsigned int ID) { id_VAO = ID; };
	unsigned int &GetIDVBO() { return id_VBO; };
	void SetIdVBO(unsigned int ID) { id_VBO = ID; };

protected:
	unsigned int id;
	unsigned int id_VAO;
	unsigned int id_VBO;
};