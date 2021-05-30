#include "ofApp.h"
//#include <boost/progress.hpp>

glm::vec3 CalcIntersectionPoint(const glm::vec3 & a, const glm::vec3& b, const glm::vec3 & n, const glm::vec3 & p) {
    glm::vec3 ret;
    auto pa = p - a;
    auto pb = p - b;
    double dot_a = glm::dot(pa, n);
    double dot_b = glm::dot(pb, n);
    
//    double MIN_DOT_TH = 0.000001;
//    if(fabs(dot_a) < MIN_DOT_TH) dot_a = 0;
//    if(fabs(dot_b) < MIN_DOT_TH) dot_b = 0;

    // 交点なし
    if( dot_a == 0 && dot_b == 0) return ret;
    //if (dot_a * dot_b > 0) return ret;
    
    cout << "mmm" << endl;
    auto ab = b - a;
    double ratio = fabs(dot_a) / (fabs(dot_a) + fabs(dot_b) );
    ret = a + ab * (ratio);
    return ret;
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofDisableAntiAliasing();
    ofDisableSmoothing();
    ofDisableArbTex();
    ofBackground(224);

    ofTrueTypeFont::setGlobalDpi(72);
    ofTrueTypeFontSettings settings("./font/NotoSansMonoCJKjp-Regular.otf", 12);
    settings.antialiased = true;
    settings.contours = true;
    settings.simplifyAmt = 0.0;
    settings.addRanges(ofAlphabet::Japanese);
    font.load(settings);
    
    shader.load("./shader/render");
    fbo.allocate(WINDOW_WIDTH * NUM_WINDOWS, WINDOW_HEIGHT, GL_RGB);
    fbo.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
    fbo.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    int gridSize = 32;
    int offsetX = (int)fbo.getWidth() % gridSize;
    int offsetY = (int)fbo.getHeight() % gridSize;
    int numGridX = (int)fbo.getWidth() / gridSize;
    int numGridY = (int)fbo.getHeight() / gridSize;
    grid.init();
    grid.setMode(GL_LINES);
    for (int i = 0; i <= numGridX; i++) {
        int x = i * gridSize + offsetX * 0.5;
        grid.addVertex(x, 0, 0, 0.8, 0.8, 0.8, 1.0);
        grid.addVertex(x, fbo.getHeight(), 0, 0.8, 0.8, 0.8, 1.0);
    }
    for (int i = 0; i <= numGridY; i++) {
        int y = i * gridSize + offsetY * 0.5;
        grid.addVertex(0, y, 0, 0.8, 0.8, 0.8, 1.0);
        grid.addVertex(fbo.getWidth(), y, 0, 0.8, 0.8, 0.8, 1.0);
    }
    
    cam.setNearClip(1);
    cam.setFarClip(10000);
    cam.setScale(0.5);
    cam.enableOrtho();
    cam.begin();
    cam.end();
    
    double minX, minY;
    lonlat2xy(MIN_LON, MIN_LAT, MID_LON, MID_LAT, &minX, &minY);
    double maxX, maxY;
    lonlat2xy(MAX_LON, MAX_LAT, MID_LON, MID_LAT, &maxX, &maxY);
    quadtree = QuadTree<Mesh::Ptr>(Bound(minX * 0.1, maxY * 0.1, abs(maxX - minX) * 0.1, abs(minY - maxY) * 0.1), 8, 4);
    quadtree2 = QuadTree<Label::Ptr>(Bound(minX * 0.1, maxY * 0.1, abs(maxX - minX) * 0.1, abs(minY - maxY) * 0.1), 8, 4);

//    loadTown();
//    loadGaiku();
    loadWaterArea();
    loadGeometry();
    loadLand();
    loadAdminArea();
//    loadDisaster();
    loadFacility();
    loadTourism();
    loadTraffic();
}

//--------------------------------------------------------------
void ofApp::update(){
    fbo.begin();
    ofClear(255, 255);

//    shader.begin();
//    shader.setUniform2f("hatching", 0, 0);
//    grid.draw();
//    shader.end();

    cam.begin();
    
    auto a = cam.screenToWorld(glm::vec3(0, 0, 0));
    auto b = cam.screenToWorld(glm::vec3(fbo.getWidth(), fbo.getHeight(), 0));
    auto items = quadtree.getObjectsInBound({min(a.x, b.x), min(a.y, b.y), abs(a.x - b.x), abs(a.y - b.y)});
    
    shader.begin();
    for (auto & i : items) {
        auto & data = i->data;
        shader.setUniform2fv("hatching",data->param.step);
        if (data->param.mode == GL_POINTS) glPointSize(data->param.pointSize);
        data->draw();
    }
    shader.end();
    cam.end();
    
    drawLabel();

    fbo.end();
    
    server.publishTexture(&fbo.getTexture());
    ofSetWindowTitle(to_string(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    if (bDrawFull) fbo.getTexture().draw(0, 0, ofGetWidth(), ofGetHeight());
    else fbo.getTexture().drawSubsection(0, 0, ofGetWidth(), ofGetHeight(), screenOffset, 0);
}

void ofApp::drawLabel() {
    glEnable(GL_BLEND);
    glBlendSeparatedAlpha();
    ofSetColor(0, 0, 0, 255);
    auto a = cam.screenToWorld(glm::vec3(0, 0, 0));
    auto b = cam.screenToWorld(glm::vec3(fbo.getWidth(), fbo.getHeight(), 0));
    auto items2 = quadtree2.getObjectsInBound({min(a.x, b.x), min(a.y, b.y), abs(a.x - b.x), abs(a.y - b.y)});
    for (auto & i : items2) {
        auto sp = cam.worldToScreen(glm::vec3( i->data->x, i->data->y, 0));
        ofPushMatrix();
        ofTranslate(sp.x, sp.y);
//        ofScale(0.5f, 0.5f, 1.0f);
        //font.drawStringAsShapes(i->data->name, 0, 0);
        auto mesh = font.getStringMesh(i->data->name, 0, 0);
        font.getFontTexture().bind();
        mesh.draw();
        font.getFontTexture().unbind();
        ofPopMatrix();
    }
    glDisable(GL_BLEND);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    static const int speed = 50;
    if (key >= '1' && key <= '4') {
        screenOffset = (key - '1') * 1920;
    } else if (key == 'd') {
        cam.setPosition(cam.getPosition() + glm::vec3(speed, 0, 0));
    } else if (key == 'a') {
        cam.setPosition(cam.getPosition() + glm::vec3(-speed, 0, 0));
    } else if (key == 'w') {
        cam.setPosition(cam.getPosition() + glm::vec3(0, speed, 0));
    } else if (key == 's') {
        cam.setPosition(cam.getPosition() + glm::vec3(0, -speed, 0));
    } else if (key == 'z') {
        cam.setScale(cam.getScale() - 0.1f);
    } else if (key == 'x') {
        cam.setScale(cam.getScale() + 0.1f);
    } else if (key == 'n') {
        cam.rotateDeg(1, glm::vec3(0, 0, 1));
    } else if (key == 'f') {
        bDrawFull = !bDrawFull;
        if (bDrawFull) {
            ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT / NUM_WINDOWS);
        } else {
            ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
        }
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
