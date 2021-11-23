#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxEasyCam.h"
#include "ofxLight.h"
#include <iostream>
#include <vector>

#define FOV  60.0f
#define NEAR 1.0f
#define FAR  100.0f
#define BUFSIZE 512


class testApp : public ofBaseApp{

 public:
  void setup();
  void update();
  void draw();
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  
  void drawBox(GLenum mode = GL_RENDER);
  void pick(int x, int y, std::vector<int>& hitList);
  void selectThisSide(GLuint hits, GLuint *buf, std::vector<int>& hitList);
 
  ofxEasyCam   cam;
  ofxLight   light;
  std::vector<int> selectedList;
 
 private:
  template<typename T> bool contains(std::vector<T>& hitList, T element){
   return std::find( hitList.begin(),hitList.end() , element )!= hitList.end(); 
  }
};

#endif

