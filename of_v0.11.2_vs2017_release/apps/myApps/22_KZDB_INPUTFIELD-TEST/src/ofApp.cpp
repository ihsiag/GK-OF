#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ImGuiIO& io = ImGui::GetIO();
    ofDirectory dataDirectory(ofToDataPath("/data", true));
    io.Fonts->AddFontFromFileTTF("data/font/NotoSansJP-Regular.otf", 20.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //io.ImeWindowHandle = ofGetWin32Window();

    ImGuiPlatformIO& pio = ImGui::GetPlatformIO();

    gui.setup();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    /*ImVec2 _pos = ImVec2(0, 0);
    ImGuiViewport* _vp = ImGui::GetWindowViewport();
    pio.Platform_SetImeInputPos(_vp, _pos);*/
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    //imguiIMMCommunication();
    float floatValue = 19;
    gui.begin();
    //pio->Platform_SetImeInputPos(ImGuiViewport * vp, ImVec2 pos);
    ImGui::Text(u8"“ú–{Œê‚Ì•¶Žš—ñ");
    
    static char str0[128] = "";
    ImGui::InputText(u8"“ü—Í‚µ‚Ä‚­‚¾‚³‚¢", str0, IM_ARRAYSIZE(str0));
    //ImGui::SameLine(); HelpMarker("USER:\nHold SHIFT or use mouse to select text.\n" "CTRL+Left/Right to word jump.\n" "CTRL+A or double-click to select all.\n" "CTRL+X,CTRL+C,CTRL+V clipboard.\n" "CTRL+Z,CTRL+Y undo/redo.\n" "ESCAPE to revert.\n\nPROGRAMMER:\nYou can use the ImGuiInputTextFlags_CallbackResize facility if you need to wire InputText() to a dynamic string type. See misc/cpp/imgui_stdlib.h for an example (this is not demonstrated in imgui_demo.cpp).");

    static char str1[128] = "";
    ImGui::InputTextWithHint("input text (w/ hint)", "enter text here", str1, IM_ARRAYSIZE(str1));

    gui.end();
}

void ofApp::HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
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
