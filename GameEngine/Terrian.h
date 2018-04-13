#ifndef TERRIAN_H
#define TERRIAN_H

#include "StaticEntity.h"
#include "Renderable.h"

class Terrian : public virtual Renderable, public virtual StaticEntity {
private:
public:
	void render() override {

	}

	void update() override {
		//LOG("Updating Terrian!!!!");
	}

	void onWorldTickUpdate() override {

	}
};

#endif