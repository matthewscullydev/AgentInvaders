#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);

	// create an image for sprites being spawned by emitter
	//

	if (defaultImage.load("images/EnemyAgent.png")) {
		imageLoaded = true;
	}

	if (bgImage.load("images/bg.png")) {
		bgImageloaded = true;
	}

	if (title.load("images/title.png")) {
		titleLoaded = true;
	}

	else {
		cout << "Can't open image file" << endl;
		ofExit();
	}

	

	// create an array of emitters and set their position;
	//
	
//	turret = new Emitter();

	turret = new AgentEmitter();

	turret->pos = glm::vec3(ofRandom(0,1024), ofRandom(0, 768), 0);
	turret->drawable = true; 
	turret->setChildImage(defaultImage);
	turret->start();

	
	gui.setup();
	gui.add(nEnergyslider.setup("Energy Levels", 20, 20, 100));
	gui.add(rate.setup("Agent Rate", 3, .5, 5));
	gui.add(life.setup("Agent Life", 5, 0, 10));

	gui.add(numAgentSlider.setup("Number of Agents", 1, 1, 5));

	//gui.add(velocity.setup("velocity", ofVec3f(0, 0, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
	bHide = false;

	//buttons
	gui.add(toggle2.setup("show sprite", true));
	//gui.add(toggle.setup("show heading vector", false));

	//player sliders
	gui.add(vec2Slider.setup("X is speed Y is scale", ofVec2f(5.25, 1),
		ofVec2f(0, 1), ofVec2f(20, 3)));

	//player 

	tri = Player(glm::vec3(-25, 25, 0), glm::vec3(25, 25, 0),
		glm::vec3(0, -25, 0));

	tri.pos = glm::vec3(ofGetWindowWidth() / 2.0,
		ofGetWindowHeight() / 2.0 + 200, 0);

	//startTime = ofGetElapsedTimeMillis();

}

//--------------------------------------------------------------
void ofApp::update() {
	turret->setRate(rate);
	turret->setLifespan(life * 1000);    // convert to milliseconds 
	turret->setVelocity(ofVec3f(velocity->x, velocity->y, velocity->z));
	turret->update();

	turret->setNum(numAgentSlider);

	if (!start_emit && tri.nEnergy > 0) {
		tri.setEnergy(nEnergyslider);
	}
	

	if (keymap[OF_KEY_RIGHT]) {
		tri.rot += 4;

	}
	if (keymap[OF_KEY_LEFT]) {
		tri.rot -= 4;
	}
	if (keymap[OF_KEY_UP]) {
		glm::vec3 speedvec = glm::vec3(tri.speed, tri.speed, 0);
		glm::vec3 finalvec = speedvec * tri.heading();
		tri.pos += finalvec;
	}
	if (keymap[OF_KEY_DOWN]) {
		glm::vec3 speedvec = glm::vec3(-tri.speed, -tri.speed, 0);
		glm::vec3 finalvec = speedvec * tri.heading();
		tri.pos += finalvec;
	}

	/*
	if (toggle) {
		tri.headshow = true;
	}
	else {
		tri.headshow = false;
	}
*/
	if (toggle2) {
		tri.showsprite = true;

	}
	else {
		tri.showsprite = false;
		for (int i = 0; i < turret->sys->sprites.size(); i++) {
			turret->sys->sprites.at(i).bShowImage = false;
		}
	}

	if (tri.nEnergy < 0) {
		tri.nEnergy = 0;
	}

	if (tri.nEnergy == 0) {
		takeTime = false;
		start_emit = false;
		showEndScr = true;
	}

	if (!start_emit) {
		turret->time = 1000;
		turret->lastSpawned = 0;
	}

}


//--------------------------------------------------------------
void ofApp::draw(){

	//string emitTime;
	string endTime;


	bgImage.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
	tri.draw();



	//cout << tri.colVal << endl;



	if (!start_emit && tri.nEnergy > 0) {
		ofResetElapsedTimeCounter();
		
		if (fullscreenTrue) {
			title.draw(770, 275);
		}
		else {
			title.draw(450, 200);
		}
		string instructions;
		instructions = "Press space to start";
		ofDrawBitmapString(instructions, (ofGetWindowWidth()/2)-50, ofGetWindowHeight()/2);

	}

	if (start_emit) {
		turret->draw();
		takeTime = true;
		
		for (int i = 0; i < turret->sys->sprites.size(); i++) {
			//change position of Agent
			turret->sys->sprites.at(i).pos += (tri.pos - turret->sys->sprites.at(i).pos)/100;
			
			//change rotation of Agent
			ofVec3f rotatespr = turret->sys->sprites.at(i).pos - tri.pos;

			ofVec3f normalizedv1 = glm::normalize(glm::vec3(rotatespr));
			ofVec3f normalizedv2 = glm::normalize((turret->sys->sprites.at(i).heading()));
	
			float dotRot = normalizedv1.dot(normalizedv2);
			float rads = acos(dotRot);
	
			turret->sys->sprites.at(i).rot += rads;
		
			//collision check&& abs(tri.pos.y - turret->sys->sprites.at(i).pos.y)
		
			if ((glm::distance(tri.pos, turret->sys->sprites.at(i).pos)) < turret->sys->sprites.at(i).Sradius + tri.Pradius) {

				turret->sys->sprites.at(i).lifespan = 0;
				tri.nEnergy--;
			}

		}

	}


	if(start_emit && takeTime){
		

		//timer stuff 
		
		
		emitTime = "Time Alive: " + std::to_string( ofGetElapsedTimef()) + " Seconds\n";
		ofSetColor(ofColor::white);
		ofDrawBitmapString(emitTime, ofGetWindowWidth() - 170, 40);
		//cout << emitTime;
		
	}

	string energystr;
	energystr += "Energy: " + std::to_string(tri.nEnergy) + "/" + std::to_string(nEnergyslider);
	ofSetColor(ofColor::white);
	ofDrawBitmapString(energystr, ofGetWindowWidth() - 170, 70);
	
	string str;
	str += "Frame Rate: " + std::to_string(ofGetFrameRate());
	ofSetColor(ofColor::white);
	ofDrawBitmapString(str, ofGetWindowWidth() - 170, 15);
	
	//ofDrawBitmapString(ofGetFrameRate(), ofGetScreenWidth()-100, 50);



	tri.speed = vec2Slider->x;
	tri.scale = vec2Slider->y;



	//collision checking

	if (tri.pos.x > ofGetWindowWidth()) {
		tri.pos.x = ofGetWindowWidth();
	}
	if (tri.pos.x < 0) {
		tri.pos.x = 0;
	}

	if (tri.pos.y > ofGetWindowHeight()) {
		tri.pos.y = ofGetWindowHeight();
	}
	if (tri.pos.y < 0) {
		tri.pos.y = 0;
	}


	if (!bHide) {
		gui.draw();
	}

	//if (tri.nEnergy == 0 && !takeTime) {
	//	ofDrawBitmapString(emitTime,ofGetWindowWidth()/2, ofGetWindowHeight() / 2);
	//}

	if (showEndScr) {
		string first;
		
		first = "\nGame Over\nPress R to Restart";
		turret->time = 0;
		turret->lastSpawned = 0;
		//cout << turret->lastSpawned << endl;
		//cout << turret->time << endl;
		ofDrawBitmapString(first, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
		ofDrawBitmapString(emitTime, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
		
	}


}


//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
//	cout << "mouse( " << x << "," << y << ")" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

void ofApp::keyPressed(int key) {
	keymap[key] = true;
	switch (key) {
	case 'C':
	case 'c':
		break;
	case 'F':
	case 'f':
		ofToggleFullscreen();
		if (!fullscreenTrue) {
			fullscreenTrue = true;
		}
		else {
			fullscreenTrue = false;
		}
		break;
	case 'H':
	case 'h':
		bHide = !bHide;
		break;
	case 'r':
		tri.nEnergy = 20;
		showEndScr = false;
		
	//	if (start_emit) {
		//	start_emit = false;
		//}
		break;
	case 's':
		break;
	case 'u':
		break;
	case OF_KEY_ALT:
		break;
	case OF_KEY_CONTROL:
		break;
	case OF_KEY_SHIFT:
		break;
	case OF_KEY_DEL:
		break;
	case ' ':
		
		turret->sys->sprites.clear();
		start_emit = true;
		//ofResetElapsedTimeCounter();
	
	}
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	keymap[key] = false;
	switch (key) {
	case OF_KEY_LEFT:
	case OF_KEY_RIGHT:
	case OF_KEY_UP:
	case OF_KEY_DOWN:
		break;
	case OF_KEY_ALT:
		break;
	case OF_KEY_CONTROL:
		break;
	case OF_KEY_SHIFT:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

