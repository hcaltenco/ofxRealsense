#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	width = 640;
	height = 480;

	//farThreshold = 0;
	//nearThreshold = 255;
	//sender.setup(HOST, PORT);

	settings.loadFile("settings.xml");
	nearThreshold = settings.getValue("settings:nearThreshold", 255);
	farThreshold = settings.getValue("settings:farThreshold", 0);

	savesettings = false; 

	//Add desired streams to configuration
	depthChannel.allocate(width, height, OF_IMAGE_GRAYSCALE);
	grayThreshNear.allocate(width,height);
	grayThreshFar.allocate(width,height);
	
	cfg.enable_stream(RS2_STREAM_DEPTH, width, height, RS2_FORMAT_Z16, 30);

	//Instruct pipeline to start streaming with the requested configuration
	pipe.start(cfg);

	frames = pipe.wait_for_frames();
}

//--------------------------------------------------------------
void ofApp::update(){

	frameset newFrames;
	if (pipe.poll_for_frames(&newFrames))
		frames = newFrames;
	
	// depth
	depth_frame depthFrame = frames.get_depth_frame();
	const unsigned char *ptr = (unsigned char *)depthFrame.get_data();
	for (int i = 0; i < width * height; i++) {
		unsigned short d = *((unsigned short *)(ptr + 2 * i)) * 10 / 255;
		*(depthChannel.getPixels().getData() + i) = d;
	}

	grayImage.setFromPixels(depthChannel);

	grayThreshNear = grayImage;
	grayThreshFar = grayImage;
	grayThreshNear.threshold(nearThreshold, true);
	grayThreshFar.threshold(farThreshold);

	cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);

	grayImage.flagImageChanged(); 		// update the cv images

	contourFinder.findContours(grayImage, 300, 20000, 1, false, false);

	for (int i = 0; i < contourFinder.nBlobs; i++) 
	{
		handx = ofMap(contourFinder.blobs[i].centroid.x, 0, 640, 0, 1920);
		handy = ofMap(contourFinder.blobs[i].centroid.y, 0, 480, 0, 1080);

	}
	/*
	ofxOscMessage m;
	m.setAddress(string(MESSAGE));
	m.addFloatArg((float)handx);
	//m.addFloatArg((float)handy);
	sender.sendMessage(m, false);

	depthChannel.update();*/

}

//--------------------------------------------------------------
void ofApp::draw() {

	grayImage.draw(0, 0, 640, 480);
	contourFinder.draw(0, 0, 640, 480);
	
	ofColor(255, 0, 0);
	ofCircle(handx, handy, 20);
	ofColor(255, 255, 255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {
	case '>':
	case '.':
		farThreshold++;
		if (farThreshold > 255)
			farThreshold = 255;
		break;

	case '<':
	case ',':
		farThreshold--;
		if (farThreshold < 0)
			farThreshold = 0;
		break;

	case '+':
	case '=':
		nearThreshold++;
		if (nearThreshold > 255) 
			nearThreshold = 255;
		break;

	case '-':
		nearThreshold--;
		if (nearThreshold < 0) 
			nearThreshold = 0;
		break;

	case 'q' :
		settings.setValue("settings:farThreshold", farThreshold);
		settings.setValue("settings:nearThreshold", nearThreshold);
		settings.saveFile("settings.xml");
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}