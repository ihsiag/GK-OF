#pragma once

#include "ofMain.h"

class Panel {
public:
  using Ptr = shared_ptr<Panel>;
  Panel(float x, float y, float w, float h)
  : x(x), y(y), w(w), h(h) {
    float hue = ofRandomuf();
    col = ofFloatColor::fromHsb(hue, 1, 1);
  }
  
  void draw() const {
    glColor4fv(&col[0]);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
  }
  
  bool inside(float px, float py) const {
    return px > x && px < (x + w) && py > y && py < (y + h);
  }
  
  float x, y;
  float w, h;
  ofFloatColor col;
  
};

static vector<Panel::Ptr> divide(Panel::Ptr & p) {
  const float x = p->x;
  const float y = p->y;
  const float w = p->w * 0.5;
  const float h = p->h * 0.5;
  
  vector<Panel::Ptr> result;
  result.emplace_back(make_shared<Panel>(x, y, w, h));
  result.emplace_back(make_shared<Panel>(x + w, y, w, h));
  result.emplace_back(make_shared<Panel>(x + w, y + h, w, h));
  result.emplace_back(make_shared<Panel>(x, y + h, w, h));
  return result;
}

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
  
  vector<Panel::Ptr> panels;
};
