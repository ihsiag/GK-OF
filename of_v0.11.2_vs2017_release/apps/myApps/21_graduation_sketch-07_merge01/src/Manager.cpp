#include "Manager.h"
#if defined(TARGET_WIN32)
#include <shlobj.h>
#endif

std::shared_ptr<myManager> myManager::instance;


void* HRGetmyManager() {
    return myManager::getInstance().get();
}

void HRBindMainFBO() {
    glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    ofPushStyle();

    glViewport(0, 0, HR_WIDTH, HR_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, HR_WIDTH, HR_HEIGHT, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    myManager::getInstance()->fbo.begin(OF_FBOMODE_NODEFAULTS);
}

void HRUnbindMainFBO() {
    myManager::getInstance()->fbo.end();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    ofPopStyle();
    glPopAttrib();
    glPopClientAttrib();
}

void myManager::addRenderer(myRenderer* r) {
    scenes.push_back(r);
}

void myManager::setup() {
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    ofDisableAlphaBlending();
    ofDisableSmoothing();
    ofDisableAntiAliasing();
    ofDisableBlendMode();
    ofDisableAntiAliasing();

    std::cout << scenes.size() << std::endl;
    for (myRenderer* r : scenes) {
        glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        //ofPushStyle();
        r->setup();
        //ofPopStyle();
        glPopAttrib();
        glPopClientAttrib();
    }

    currentSceneIndex = 0;
    scenes[currentSceneIndex]->sceneStarted();
    sceneStartSec = ofGetElapsedTimef();
}

void myManager::update() {
}

void myManager::draw() {
    if (!bPaused) {
        float now = ofGetElapsedTimef();
        float elapsed = now - sceneStartSec; //fmodf(duration, duration);

        currentSceneSec = elapsed;
        currentSceneFloatFrame = elapsed * HR_FPS;
        int frame = roundf(currentSceneFloatFrame);
        if (frame == currentSceneFrame) {
            if ((now - lastSec) * HR_FPS < 0.6f) {
                return;
            }
            else {
                frame += 1;
            }
        }
        currentSceneFrame = frame;
        lastSec = now;

        myRenderer* r = scenes[currentSceneIndex];
        HRBindMainFBO();
        glClearColor(0, 0, 0, 0);
        r->render();
        HRUnbindMainFBO();
    }

    glm::vec2 size = ofGetWindowSize();
    glViewport(0, 0, size.x, size.y);

    glClearColor(0.05, 0.05, 0.05, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);


    glColor3f(1, 1, 1);
    if (viewScale < 0) {
        float s = MIN(size.x / HR_WIDTH, size.y / HR_HEIGHT);
        viewOffset = { (size.x - HR_WIDTH * s) / 2, (size.y - HR_HEIGHT * s) / 2 };
        fbo.draw(viewOffset.x, viewOffset.y, HR_WIDTH * s, HR_HEIGHT * s);
    }
    else {
        if (size.x >= HR_WIDTH * viewScale && size.y >= HR_HEIGHT * viewScale) {
            viewOffset = { (size.x - HR_WIDTH * viewScale) / 2, (size.y - HR_HEIGHT * viewScale) / 2 };
        }
        fbo.draw(viewOffset.x, viewOffset.y, HR_WIDTH * viewScale, HR_HEIGHT * viewScale);
    }

    if (bShowFramerate) {
        glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        ofPushStyle();
        ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 10);
        ofPopStyle();
        glPopAttrib();
        glPopClientAttrib();
    }
}

void myManager::keyPressed(int key) {
    glm::vec2 origin = glm::vec2(int((ofGetWidth() - HR_WIDTH) / 2), int((ofGetHeight() - HR_HEIGHT) / 2));
    switch (key) {
    case OF_KEY_RIGHT:
        scenes[currentSceneIndex]->sceneEnded();
        currentSceneIndex++;
        currentSceneIndex %= scenes.size();
        scenes[currentSceneIndex]->sceneStarted();
        sceneStartSec = ofGetElapsedTimef();
        break;

    case OF_KEY_LEFT:
        scenes[currentSceneIndex]->sceneEnded();
        currentSceneIndex--;
        if (currentSceneIndex < 0) currentSceneIndex += scenes.size();
        scenes[currentSceneIndex]->sceneStarted();
        sceneStartSec = ofGetElapsedTimef();
        break;

    case 'd':
        bShowFramerate = !bShowFramerate;
        break;
    case '0':
        viewScale = -1;
        break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        viewScale = 1 + key - '1';
        break;
    case 'f':
        ofToggleFullscreen();
        viewOffset = glm::vec2(0, 0);
        break;

    case ' ':
        bPaused = !bPaused;
        break;
    }

    if (currentSceneIndex > -1) {
        scenes[currentSceneIndex]->keyPressed(key);
    }
}

void myManager::mousePressed(int x, int y, int button) {
    dragPos = { x, y };
    if (currentSceneIndex > -1) {
        scenes[currentSceneIndex]->mousePressed(x, y);
    }
}

void myManager::mouseDragged(int x, int y, int button) {
    if (button == 0) {
        viewOffset.x += x - dragPos.x;;
        viewOffset.y += y - dragPos.y;
        dragPos = { x, y };
    }

    if (currentSceneIndex > -1) {
        scenes[currentSceneIndex]->mouseDragged(x, y);
    }
}

void myManager::mouseReleased(int x, int y, int button) {
    if (currentSceneIndex > -1) {
        scenes[currentSceneIndex]->mouseReleased(x, y);
    }
}