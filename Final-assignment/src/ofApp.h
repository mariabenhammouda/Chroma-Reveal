#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxKinect.h"

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
    void exit();
    ofxKinect kinect;
    ofxCv::ContourFinder contour;
    ofColor color;
    ofVideoGrabber webcam;
    ofImage img;
    ofImage myImg;
    bool screenshot=false;
    
    void addPoint();

        vector    <shared_ptr<ofPolyline>> brushStrokes; // this is the lines that are generated (having them in a vector will help with controling the colors)
        //vector    <shared_ptr<int[20]>> linepoints; // this is to store each line points
        vector    <shared_ptr<ofVec2f>> linepoints; // this is to store each line points

        // brush variables(for smothing)
        int stepSize;
        ofVec2f brushLoc;
};
