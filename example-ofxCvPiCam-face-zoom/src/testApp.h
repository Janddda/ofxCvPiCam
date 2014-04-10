#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxCvPiCam.h"
class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
    ofxCvPiCam cam;
    cv::Mat frame;
    ofImage cropped;
	ofxCv::ObjectFinder objectFinder;
};
