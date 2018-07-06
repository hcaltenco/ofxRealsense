#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxXmlSettings.h"
#include "ofxOsc.h"
#include <librealsense2/rs.hpp>

//Defaults for OSC:
#define HOST "localhost"
#define PORT 6448
#define MESSAGE "/wek/inputs"

using namespace rs2;


class ofApp : public ofBaseApp{

	private:
	config cfg;
	pipeline pipe;
	frameset frames;
	ofImage depthChannel;

	int width, height;

	public:
		void setup();
		void update();
		void draw();
		
		ofxCvColorImage colorImg;
		ofxCvGrayscaleImage grayImage;
		ofxCvGrayscaleImage grayThreshNear;
		ofxCvGrayscaleImage grayThreshFar;
		ofxCvContourFinder contourFinder;
		ofxXmlSettings settings;
		
		//OSC sender:
		ofxOscSender sender;

		int farThreshold, nearThreshold;
		bool savesettings;
		float handx, handy;

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
