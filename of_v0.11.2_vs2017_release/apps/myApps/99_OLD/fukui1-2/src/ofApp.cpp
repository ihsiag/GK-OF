#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  int num_rows = 10;
  int num_cols = 10;
  float w = ofGetWidth() / num_cols;
  float h = ofGetHeight() / num_rows;
  
  for (int iy = 0; iy < num_cols; iy++) {
    float y = iy * h;
    for (int ix = 0; ix < num_rows; ix++) {
      float x = ix * w;
      panels.emplace_back(make_shared<Panel>(x, y, w, h));
    }
  }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  for (auto & p : panels) p->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
  
  vector<Panel::Ptr> new_panels;
  auto it = panels.begin();
  for (; it != panels.end();) {
    if ((*it)->inside(x, y)) {
      auto & panel = *it;
      auto divided = divide(panel);
      copy(divided.begin(), divided.end(), back_inserter(new_panels));
      it = panels.erase(it);
    } else {
      ++it;
    }
  }

  if (new_panels.size()) copy(new_panels.begin(), new_panels.end(), back_inserter(panels));

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
