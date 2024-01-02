#pragma once

#include "Shape.h"

class Player : public TriangleShape {
public:
    ofImage img;
    bool headshow = false;
    bool showsprite = false;
    int nEnergy;
  
    ofVec3f colVal = (verts[2] - verts[0])*4;

    float Pradius = colVal.x;
    //constructor for player which inherits triangle shape constructor

    Player() {}
    Player(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
        : TriangleShape(p1, p2, p3), nEnergy{ 100 } {}

    //methods for player are beneath here

    glm::vec3 heading() {
        float num = ofDegToRad(rot - 90);
        glm::vec3 directionvec = glm::vec3(cos(num), sin(num), 0);
        glm::vec3 normalizedvec = glm::normalize(directionvec);
        return normalizedvec;
    };

    void draw() {
        ofPushMatrix();
        ofMultMatrix(getMatrix());

        ofDrawBitmapString(nEnergy,50,50);

        if (!showsprite) {

            ofDrawTriangle(verts[0], verts[1], verts[2]);
            //ofClear(ofColor::blueSteel);
        };

        if (showsprite) {
            this->img.load("images/ship.png");
            img.draw(-img.getWidth() / 2, -img.getHeight() / 2);
        };



        ofPopMatrix();

        //TriangleShape::draw();
        //ofSetColor(ofColor::green);
        if (headshow) {
            ofDrawLine(pos, pos + heading() * scale * 75);
        }
    };

    void setEnergy(int nEnerg) {
        this->nEnergy = nEnerg;
    }

    ofVec3f getPos() {
        return pos;
    }

};