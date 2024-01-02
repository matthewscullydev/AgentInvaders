#pragma once

#include "Shape.h"

class Sprite : public TriangleShape {
public:
	// some functions for highlighting when selected
	//
	ofVec3f colVal1 = (verts[1] - verts[0])/2;

	float Sradius = colVal1.x;

	bool startup = true;

	void draw() {
	
		if (startup) {
			pos = ofVec3f(ofRandom(0,ofGetScreenWidth()), ofRandom(0, ofGetScreenHeight()), 0);
			rot = ofRandom(0, 360);

			startup = false;
		}
		if (bShowImage) {
			ofPushMatrix();
			ofSetColor(ofColor::white);
			ofMultMatrix(getMatrix());
			spriteImage.draw(-spriteImage.getWidth() / 2, -spriteImage.getHeight() / 2.0);
			ofPopMatrix();
		}
		else
		{
			if (bHighlight) ofSetColor(ofColor::white);
			else ofSetColor(ofColor::yellow);
			ofFill();
			TriangleShape::draw();
		}

	}


	float age() {
		return (ofGetElapsedTimeMillis() - birthtime);
	}

	void setImage(ofImage img) {
		spriteImage = img;
		bShowImage = true;
		width = img.getWidth();
		height = img.getHeight();
	}

	bool inside(const glm::vec3 p);

	void setSelected(bool state) { bSelected = state; }
	void setHighlight(bool state) { bHighlight = state; }
	bool isSelected() { return bSelected; }
	bool isHighlight() { return bHighlight; }

	
	glm::vec3 heading() {
		return (glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 0, 1)) * glm::vec4(0, 1, 0, 1));
	}

	bool bHighlight = false;
	bool bSelected = false;
	bool bShowImage = false;

	//maybe pos?
	glm::vec3 velocity = glm::vec3(0, 0, 0);

	

	float birthtime = 0; // elapsed time in ms
	float lifespan = -1;  //  time in ms
	string name =  "UnammedSprite";
	float width = 40;
	float height = 40;

	ofImage spriteImage;
};

