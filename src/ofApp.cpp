#include "ofApp.h"

//-----------------------------------------------------------------------------------------
//
void ofApp::setup()
{
	fontSmall.loadFont("Fonts/DIN.otf", 8 );
	
	// Give us a starting point for the camera
	camera.setNearClip(0.01f);
	camera.setPosition( 0, 4, 40 );
	camera.setMovementMaxSpeed( 0.1f );
    
    h = 30; // initializing height for the height of the mesh
    w = 30; // initializing width for the width of the mesh
    // sets up vertices and colors of each mesh at i
    for(int i=0; i<number; i++) {
        for(int y=0; y<h; y++) {
            for(int x=0; x<w; x++) {
                mesh[i].addVertex(ofPoint((x-w/2), (y-h/2), 0));
                mesh[i].addColor(ofColor(255, 255, 255));
            }
        }
        // sets up the indices of triangles to make a grid of triangles
        for(int y=0; y<h-1; y++) {
            for(int x=0; x<w-1; x++) {
                
                int index1 = x + w * y;
                int index2 = x+1 + w * y;
                int index3 = x + w * (y+1);
                int index4 = x+1 + w * (y+1);
                
                mesh[i].addTriangle(index1, index2, index3);
                mesh[i].addTriangle(index2, index4, index3);
            }
        }
        
            setNormals(mesh[i]); // sets normals to surface
    }
   
    

    
    
    light1.enable(); // enables light
    
    
	
}

//-----------------------------------------------------------------------------------------
//
void ofApp::update()

{
    float time = ofGetElapsedTimef(); // time is equal to the amount of time passed
    // changes the vertices for each mesh at j
    for(int j=0; j<number; j++) {
        for(int y=0; y<h; y++) {
            for(int x=0; x<w; x++) {
                // vertex index
                int i = x + w * y;
                
                ofPoint pt = mesh[j].getVertex(i);
                float noise = ofNoise(x, y, time * 0.5); // Perlin noise value
                float rNoise = ofSignedNoise(x*0.5, y*0.3, time*0.1); // Creates a Perlin signed noise value for the red value of the mesh color
//  comment above line and uncomment line below for a variation of blue, purple, and red colors
//               float rNoise = ofSignedNoise(x*0.5, y*0.3, time);
                float bNoise = ofSignedNoise(x*0.5, y*0.3, time*0.1); // creates a Perlin signed noise value for the blue value of the mesh
                pt.z = noise ; // assigns noise to the z value so the noise affects the z space of the mesh
                
                
                mesh[j].setVertex(i, pt);
                mesh[j].setColor(i, ofColor(250*rNoise, 0, 250*bNoise)); // sets color of mesh
                // note: only using red and blue to make a purple color, then adding the rNoise and bNoise to change the values of red and blue to make different shades of purple
            }
        }
        
        setNormals(mesh[j]); // updates the normals for each mesh at j
    }
    
    
}

//-----------------------------------------------------------------------------------------
//
void ofApp::draw()
{
	ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);	
	
	ofEnableDepthTest(); // allows rendering to happen according to the z depth
	
	camera.begin(); // starts drawing camera view
    
    // grid commented out to get rid of it
	
//		// draw a grid on the floor
//		ofSetColor( ofColor(60) );
//		ofPushMatrix();
//			ofRotate(90, 0, 0, -1);
//			ofDrawGridPlane( 10 );
//		ofPopMatrix();
    
    ofPushMatrix();
    //ofRotate(90, -1, 0, 0); // rotates the meshes so they are on the 'floor'
    ofTranslate(0, 0, -2);
    for(int i=0; i<number; i++) {
        
        ofRotate(ofRadToDeg(70)); // rotates each mesh 70 degrees to get a rounder/flower looking shape
        
        mesh[i].draw(); // draws the mesh
        
        
    }
    ofPopMatrix();
 
	camera.end();

	ofSetColor( ofColor::white ); // sets color for framerate text
	ofDisableDepthTest(); // stops drawing to the z buffer


	fontSmall.drawStringShadowed(ofToString(ofGetFrameRate(),2), ofGetWidth()-35, ofGetHeight() - 6, ofColor::whiteSmoke, ofColor::black ); // draws current framerate at bottom of corner
    
}


//-----------------------------------------------------------------------------------------//
//Universal function which sets normals for the triangle mesh
void ofApp::setNormals( ofMesh &mesh ){
    
    //The number of the vertices
    int nV = mesh.getNumVertices();
    
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    
    vector<ofPoint> norm( nV ); //Array for the normals
    
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
        
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}





void ofApp::keyPressed(int key)
{
	if( key == 'f' )
	{
		ofToggleFullscreen();
	}
}
