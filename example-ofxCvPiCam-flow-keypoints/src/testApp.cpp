#include "testApp.h"

using namespace cv;
using namespace ofxCv;

void testApp::setup(){
    grabber.setup(160,120,false);
}

void testApp::update(){
    frame = grabber.grab();
    if(!frame.empty()){
        flow.calcOpticalFlow(frame);
	}
}

void testApp::draw(){
    if(!frame.empty()) drawMat(frame,0,0);
	flow.draw();
	if(ofGetMousePressed()){
		ofNoFill();
		ofRect(rect);
	}
}

void testApp::mouseDragged(int x, int y, int button){
	ofVec2f p2(x,y);
	rect.set(p1,p2.x-p1.x,p2.y-p1.y);
}

void testApp::mousePressed(int x, int y, int button){
	p1.set(x,y);
}

void testApp::mouseReleased(int x, int y, int button){
    if(!frame.empty()){
        ofVec2f p2(x,y);
        rect.set(p1,p2.x-p1.x,p2.y-p1.y);
        vector<KeyPoint> keypoints;
        vector<KeyPoint> keypointsInside;
        vector<cv::Point2f> featuresToTrack;
        FAST(frame,keypoints,2);
        for(int i=0;i<keypoints.size();i++){
            if(rect.inside(toOf(keypoints[i].pt))){
                keypointsInside.push_back(keypoints[i]);
            }
        }
        #if CV_MAJOR_VERSION>=2 && (CV_MINOR_VERSION>4 || (CV_MINOR_VERSION==4 && CV_SUBMINOR_VERSION>=1))
        KeyPointsFilter::retainBest(keypointsInside,30);
        #endif
        KeyPoint::convert(keypointsInside,featuresToTrack);
        flow.setFeaturesToTrack(featuresToTrack);
    }
}

