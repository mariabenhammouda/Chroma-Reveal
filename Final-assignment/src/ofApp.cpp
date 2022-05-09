#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    font.load("Rajdhani-SemiBold.ttf", 32);
    ofSetBackgroundColor(0, 0, 0); // create a rectangle as background to conver the webcam and kinect
    kinect.init();
    kinect.open(); // initialize kinect & webcam
    webcam.setup(ofGetWidth(), ofGetHeight());
    contour.setMinAreaRadius(30); // the min and max parameters for the kinect contours
    contour.setMaxAreaRadius(130);
    ofSetLogLevel(OF_LOG_NOTICE);
    brushLoc = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);

    auto point = make_shared<ofVec2f>();
    point->x = brushLoc.x;
    point->y = brushLoc.y;
    linepoints.push_back(point);
}

//--------------------------------------------------------------
void ofApp::update() {
    webcam.update();
    kinect.update();

    // color=webcam.getPixels().getColor(320, 240);// get the color of the pixel at the webcam center
    if (kinect.isFrameNew()) { // if there is a change in the frame of kinect, set a new contour
        contour.setTargetColor(color);
        contour.setThreshold(60);
        contour.findContours(kinect);
    }
}

//--------------------------------------------------------------
void ofApp::draw() {

    kinect.draw(0, 0); // draw contour, kinect and webcam
    webcam.draw(0, 0);
    contour.draw();

     // assign the brush the color of the pixel
        //code for generative brush here
    string info = "";
    if (screenshot) { // if the user user key s for a screenshot, load the image and draw the image

        
        myImg.load("myArtwork.jpg");
        //myImg.rotate90(1);

        myImg.draw(ofGetWidth() / 2- ofGetWidth() / 3, ofGetHeight() / 2- ofGetHeight() / 3, ofGetWidth()/1.5, ofGetHeight() / 1.5);

        info += "The End\n";
    }
    else if(draww) {
        ofSetColor(225);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight()); // create a rectangle as background to conver the webcam and kinect
        this->addPoint();
        for (auto& point : linepoints) {
            //   col.setHsb(color1, 100, 100);
              // ofSetColor(col);
            this->addLine(point->x, point->y,5,20);
            //ofDrawCircle(point->x, point->y, 10);
        }
        info += "Press [s] to screenshot \nwhen you are done";
    }
    else {
        info += "Press [d] to start drawing\n";
        
        ofDrawRectangle(20, ofGetHeight() - 50,300,30);
    }
    ofSetHexColor(0x0000ff);
    //font.drawString(info, ofGetWidth() / 2, ofGetHeight() - 70);
    ofDrawBitmapString(info, 30, ofGetHeight() - 30);
    ofSetColor(225);

}
void ofApp::addPoint() {
    brushLoc.x += (ofGetMouseX() - brushLoc.x) * 0.05;
    brushLoc.y += (ofGetMouseY() - brushLoc.y) * 0.05;
    auto point = make_shared<ofVec2f>();
    point->x = brushLoc.x;
    point->y = brushLoc.y;
    linepoints.push_back(point);
}
void ofApp::addLine(float x, float y, int r, int num) {
    try {
        color = webcam.getPixels().getColor(ofGetWidth() - x, y);
    }
    catch(const exception& e){
        color = ofColor(0, 0, 0);
    }
    ofSetColor(color,100);
    ofDrawCircle(x,y,r);
    if (num > 0) {
        float newY = y + sin(ofRandom(0, TWO_PI)) * 12.0;
        this->addLine((x + num / 3), newY, int(ofRandom(r / 2, r + (num / 5))), num - 1);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    kinect.setCameraTiltAngle(0);
    if (key == 's'||key=='S') { // if key s is pressed, save the screen under name "myArtwork.jpg"

        printf("S\n");
        img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        img.save("myArtwork.jpg");
        printf("S2\n");
        screenshot = true; // assign screenshot bool to true
    }
    if (key == 'd' || key == 'D') {
        draww = true;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
void ofApp::exit() {
    kinect.close();
    kinect.setCameraTiltAngle(0);
    webcam.close();

    // upo closing the program, close kinect and webcam
}
