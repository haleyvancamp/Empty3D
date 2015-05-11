#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "Math/MathUtils.h"

#include "Utils/ofTrueTypeFontExt.h"
#include "Utils/Cameras/ofxWalkingFirstPersonCamera.h"
#define number 7

class ofApp : public ofBaseApp
{
	public:
		
		void setup();
		void update();
		void draw();
		void setNormals(ofMesh &mesh);

		void keyPressed(int key);
	
		ofxFirstPersonCamera	camera;
	
		ofTrueTypeFontExt		fontSmall;
    
    ofMesh mesh[number];
    
    int h;
    int w;
    
    ofLight light1;
};
