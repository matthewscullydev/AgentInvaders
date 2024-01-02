#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Emitter.h"
#include "Shape.h"
#include "Player.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		/*
		vector<Emitter *> emitters;
		int numEmitters = 10;
		*/
		Emitter  *turret = NULL;

		ofImage defaultImage;
		ofVec3f mouse_last;
		bool imageLoaded;

		bool bHide;

		//sliders

		ofxFloatSlider rate;
		ofxFloatSlider life;
		ofxVec3Slider velocity;
		ofxLabel screenSize;
		ofxVec2Slider vec2Slider;
		ofxIntSlider nEnergyslider;
		ofxIntSlider numAgentSlider;

		float speed;
		ofxToggle toggle;
		ofxToggle toggle2;
		ofxButton button;
		ofxButton button2;
		map<int, bool> keymap;
		ofxPanel gui;

		//background
		ofImage bgImage;
		bool bgImageloaded = false;
		//player 
		Player tri;

		//start emitter
		bool start_emit = false;
		//bool start_emit_time = false;
	
		//timer
		
		float counter;
		int seccounter = 0;
		bool takeTime;
		bool showEndScr = false;
		//string for time
		//string emitTime;
		string emitTime;

		//title
		ofImage title;
		bool titleLoaded = false;
		bool fullscreenTrue = false;
};


class AgentEmitter : public Emitter {
public:
	void moveSprite(Sprite* sprite) {
		Emitter::moveSprite(sprite);
	}
	void spawnSprite() {
		Emitter::spawnSprite();
	}
};

