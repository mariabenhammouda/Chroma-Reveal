#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    myImg.load("myArtwork.jpg");
    kinect.init();
    kinect.open();
    webcam.setup(640,480);
    contour.setMinAreaRadius(30);
    contour.setMaxAreaRadius(130);
        ofSetLogLevel(OF_LOG_NOTICE);
        brushLoc = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
        //
    
   // col.setHsb(0, 0, 0);
        auto point = make_shared<ofVec2f>();
        point->x = brushLoc.x;
        point->y = brushLoc.y;
        linepoints.push_back(point);

       
    
}

//--------------------------------------------------------------
void ofApp::update(){
    webcam.update();
    kinect.update();
    color=webcam.getPixels().getColor(100, 250);
    if (kinect.isFrameNew()){
        contour.setTargetColor(color);
        contour.setThreshold(60);
        contour.findContours(kinect);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
  
    kinect.draw(0,0);
    webcam.draw(0,0);
    contour.draw();
    
    
    ofSetColor(255);

    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetColor(color);
        //code for generative brush here
    this->addPoint();
        for (auto& point : linepoints) {
         //   col.setHsb(color1, 100, 100);
           // ofSetColor(col);
            ofDrawCircle(point->x, point->y, 10);
        }
    ofSetColor(255);
    if(screenshot){
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
    if (key == 's') {
       
            printf("S\n");
            img.grabScreen(0, 0, ofGetWidth(),ofGetHeight());
            img.save("myArtwork.jpg");
            printf("S2\n");
        screenshot=true;
      
       
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
}
