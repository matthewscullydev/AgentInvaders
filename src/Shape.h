#pragma once
#include "ofMain.h"

class Shape {
public:
	Shape() {}
	virtual void draw() {

		// draw a box by defaultd if not overridden
		//
		ofPushMatrix();
		ofMultMatrix(getMatrix());
		ofDrawBox(defaultSize);
		ofPopMatrix();
	}
	void setPos(ofVec3f posp) {
		pos = posp;
	}
	virtual bool inside(glm::vec3 p) {
		return false;
	}

	glm::mat4 getMatrix() {
		glm::mat4 m1 = glm::translate(glm::mat4(1.0), glm::vec3(pos));
		glm::mat4 m2 = glm::rotate(m1, glm::radians(rot), glm::vec3(0, 0, 1));
		glm::mat4 M = glm::scale(m2, glm::vec3(scale));      // added this scale if you want to change size of object
		return M;
	}
	glm::vec3 pos;
	float rot = 0.0;    // degrees 
	float scale = 1.0;
	//glm::vec3 scale = glm::vec3(1, 1, 1);
	float defaultSize = 20.0;

	vector<glm::vec3> verts;
};


class TriangleShape : public Shape {
public:
	float speed;
	TriangleShape() {
		// default data
		set(glm::vec3(20, 20, 0), glm::vec3(0, -40, 0), glm::vec3(-20, 20, 0));
	}

	TriangleShape(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
		verts.push_back(p1);
		verts.push_back(p2);
		verts.push_back(p3);
	}


	virtual void draw() {
		ofPushMatrix();
		ofMultMatrix(getMatrix());
		ofDrawTriangle(verts[0], verts[1], verts[2]);
		ofPopMatrix();
	};

	virtual bool inside(const glm::vec3 p) {
		// transform the screen space point p to the triangle's local 
	// oordinate system  (object space);  this will take into account any
	// rotation, translation or scale on the object.
	//
		glm::vec4 p2 = glm::inverse(getMatrix()) * glm::vec4(p, 1);

		glm::vec3 v1 = glm::normalize(verts[0] - p2);
		glm::vec3 v2 = glm::normalize(verts[1] - p2);
		glm::vec3 v3 = glm::normalize(verts[2] - p2);
		float a1 = glm::orientedAngle(v1, v2, glm::vec3(0, 0, 1));
		float a2 = glm::orientedAngle(v2, v3, glm::vec3(0, 0, 1));
		float a3 = glm::orientedAngle(v3, v1, glm::vec3(0, 0, 1));
		if (a1 < 0 && a2 < 0 && a3 < 0) return true;
		else return false;
	};

	void set(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
		verts.clear();
		verts.push_back(v1);
		verts.push_back(v2);
		verts.push_back(v3);
	}

};

