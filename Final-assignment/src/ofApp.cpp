#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
   
    kinect.init();
    kinect.open(); // initialize kinect & webcam
    webcam.setup(640,480);
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
void ofApp::update(){
    webcam.update();
    kinect.update();
    color=webcam.getPixels().getColor(320, 240);// get the color of the pixel at the webcam center
    if (kinect.isFrameNew()){ // if there is a change in the frame of kinect, set a new contour
        contour.setTargetColor(color);
        contour.setThreshold(60);
        contour.findContours(kinect);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
  
    kinect.draw(0,0); // draw contour, kinect and webcam
    webcam.draw(0,0);
    contour.draw();
    ofSetColor(255);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight()); // create a rectangle as background to conver the webcam and kinect
    
    ofSetColor(color); // assign the brush the color of the pixel
        //code for generative brush here
    this->addPoint();
        for (auto& point : linepoints) {
         //   col.setHsb(color1, 100, 100);
           // ofSetColor(col);
            ofDrawCircle(point->x, point->y, 10);
        }
    ofSetColor(255);
    if(screenshot){ // if the user user key s for a screenshot, load the image and draw the image
        myImg.load("myArtwork.jpg");
        myImg.draw(0,0);
    }
    
}
void ofApp::addPoint() {
    brushLoc.x += (ofGetMouseX() - brushLoc.x) * 0.01;
    brushLoc.y += (ofGetMouseY() - brushLoc.y) * 0.01;
    auto point = make_shared<ofVec2f>();
    point->x = brushLoc.x;
    point->y = brushLoc.y;
    linepoints.push_back(point);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    kinect.setCameraTiltAngle(0);
    if (key == 's') { // if key s is pressed, save the screen under name "myArtwork.jpg"
       
            printf("S\n");
            img.grabScreen(0, 0, ofGetWidth(),ofGetHeight());
            img.save("myArtwork.jpg");
            printf("S2\n");
        screenshot=true; // assign screenshot bool to true
      
       
        }
   
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::exit(){
    kinect.close();
    kinect.setCameraTiltAngle(0);
    webcam.close();
    
    // upo closing the program, close kinect and webcam
}
