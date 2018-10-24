//
// Created by bbrenk on 10/20/18.
//

#ifndef GAMEENGINE_CUBE_H
#define GAMEENGINE_CUBE_H

#include "Model.h"


class Cube : public Model {
public:
    Cube() {
        std::vector<float> skyboxVertices =
                {
                        // positions
                        -1.0f,  1.0f, -1.0f,
                        -1.0f, -1.0f, -1.0f,
                        1.0f, -1.0f, -1.0f,
                        1.0f, -1.0f, -1.0f,
                        1.0f,  1.0f, -1.0f,
                        -1.0f,  1.0f, -1.0f,

                        -1.0f, -1.0f,  1.0f,
                        -1.0f, -1.0f, -1.0f,
                        -1.0f,  1.0f, -1.0f,
                        -1.0f,  1.0f, -1.0f,
                        -1.0f,  1.0f,  1.0f,
                        -1.0f, -1.0f,  1.0f,

                        1.0f, -1.0f, -1.0f,
                        1.0f, -1.0f,  1.0f,
                        1.0f,  1.0f,  1.0f,
                        1.0f,  1.0f,  1.0f,
                        1.0f,  1.0f, -1.0f,
                        1.0f, -1.0f, -1.0f,

                        -1.0f, -1.0f,  1.0f,
                        -1.0f,  1.0f,  1.0f,
                        1.0f,  1.0f,  1.0f,
                        1.0f,  1.0f,  1.0f,
                        1.0f, -1.0f,  1.0f,
                        -1.0f, -1.0f,  1.0f,

                        -1.0f,  1.0f, -1.0f,
                        1.0f,  1.0f, -1.0f,
                        1.0f,  1.0f,  1.0f,
                        1.0f,  1.0f,  1.0f,
                        -1.0f,  1.0f,  1.0f,
                        -1.0f,  1.0f, -1.0f,

                        -1.0f, -1.0f, -1.0f,
                        -1.0f, -1.0f,  1.0f,
                        1.0f, -1.0f, -1.0f,
                        1.0f, -1.0f, -1.0f,
                        -1.0f, -1.0f,  1.0f,
                        1.0f, -1.0f,  1.0f
                };

        Object* box = new Object();

        for (auto &fl : skyboxVertices) {
            box->GetVerticies().AddFloat(fl);
        }

        this->AddObject(box);
    }
};


#endif //GAMEENGINE_CUBE_H
