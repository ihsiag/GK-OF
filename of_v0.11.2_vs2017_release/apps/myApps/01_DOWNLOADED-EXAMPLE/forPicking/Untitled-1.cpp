
testApp.cpp
#include "testApp.h"

/*

マウスプレス時にglRenderMode(GL_SELECT)で描画モードを選択モードへ変更、glPushNameでポリゴンに名前をつけて描画する。
そこから、gluPickMatrixでマウス座標上のデプスバッファを利用しヒットしたポリゴンの名前と深度情報を取り出す。
もし、ポリゴンが重なっていた場合、取り出した深度情報をもとに一番手前のものを選択する。というような流れ。
*/

//--------------------------------------------------------------
void testApp::setup(){
 ofBackground( 0, 0, 0);
 glEnable(GL_DEPTH_TEST);
 
 // init camera /////////////////////////////////////////////
 cam.setOrigin(OF_ORIGIN_ZERO);
 cam.perspective(FOV, (float)ofGetWidth()/(float)ofGetHeight() , NEAR, FAR);
 cam.position(10.0f, 10.0f, 10.0f);
 cam.eye(0.0f,0.0f,0.0f);
 cam.zoomSpeed  = 0.1;
 cam.panSpeed   = 0.1;
 
 // init light //////////////////////////////////////////////
 light.pointLight(255, 255, 255, 0, 5, 0);
 ofxSetSmoothLight(true);
 ofxLightsOn();
 light.on();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
 cam.place();
 drawBox(); 
}

//--------------------------------------------------------------
void testApp::drawBox(GLenum mode){
 glPushMatrix();
 //ネームスタックを空にする
 if (mode==GL_SELECT) glInitNames(); 
 
 // box 1 /////////////////////////
 glTranslatef(3.0f, 0.0f, 3.0f);
 if (mode==GL_SELECT) {
  glPushName(1);
 } else {
  // 選択された状態であれば色を付ける
  if(contains(selectedList, 1)) ofSetColor(255, 255,   0);
  else       ofSetColor(255, 255, 255);
 }
 glutSolidCube(2.5f);
 if (mode==GL_SELECT) glPopName();
 
 // box 2 /////////////////////////
 glTranslatef(-3.0f, 0.0f, -3.0f);
 if (mode==GL_SELECT) {
  glPushName(2);
 } else {
  // 選択された状態であれば色を付ける
  if(contains(selectedList, 2)) ofSetColor(255,   0, 255);
  else       ofSetColor(255, 255, 255);
 }
 glutSolidCube(2.5f);
 if (mode==GL_SELECT) glPopName();
 
 // box 3 /////////////////////////
 glTranslatef(-3.0f, 0.0f, -3.0f);
 if (mode==GL_SELECT) {
  glPushName(3);
 } else {
  // 選択された状態であれば色を付ける
  if(contains(selectedList, 3)) ofSetColor(  0, 255, 255);
  else       ofSetColor(255, 255, 255);
 }
 glutSolidCube(2.5f);
 if (mode==GL_SELECT) glPopName();
 glPopMatrix();
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
 pick(x, y, selectedList);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
 selectedList.clear();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
 cam.perspective(FOV, (float)w/(float)h , NEAR, FAR);
}

//--------------------------------------------------------------
void testApp::pick(int x, int y, std::vector<int>& hitList){
 GLuint selectBuf[BUFSIZE];
 GLint hits;
 
 // ビューポートの情報を習得する
 GLint viewport[4];
 glGetIntegerv(GL_VIEWPORT, viewport);

 // ピックした結果を保存するバッファ
 glSelectBuffer(BUFSIZE, selectBuf);
 // 描画モードの切り替え
 glRenderMode(GL_SELECT);
 glMatrixMode(GL_PROJECTION);    
 // gluPickMatrixは射影変換行列を変更するため変更前の行列をスタックに保存する
 glPushMatrix();
 glLoadIdentity();
 // 第３,4引数はそれぞれx,yのピックアップの判定領域
 gluPickMatrix(x,viewport[3]-y, 5.0,5.0, viewport);
 // 変更された射影変換行列をもとにもどす。
 gluPerspective( FOV, (float)viewport[2]/(float)viewport[3], NEAR, FAR );
 glMatrixMode( GL_MODELVIEW );
 drawBox(GL_SELECT);                    
 glMatrixMode(GL_PROJECTION);
 glPopMatrix();
 glMatrixMode( GL_MODELVIEW );
 // 元の描画モードに戻す　返り値にヒットした数が返る
 hits = glRenderMode(GL_RENDER);
 
 hitList.clear();
 hitList.resize(hits);
 if(hits) selectThisSide(hits, selectBuf, hitList);
}

//--------------------------------------------------------------
void testApp::selectThisSide(GLuint hits, GLuint *buf, std::vector<int>& hitList){
 unsigned int i, j;
 GLuint names, *ptr, minZ,*ptrNames, numberOfNames=0;
 ptr = (GLuint *) buf;
 minZ = 0xffffffff;
 for (i = 0; i < hits; i++) { 
  names = *ptr; // ヒットしたデータの要素数を格納
  ptr++;   // ポインタはデプスの最小値を指す
  if (*ptr < minZ) {
   numberOfNames = names; // 要素数を更新
   minZ = *ptr;   // 最小値を更新
   ptrNames = ptr+2;  // ヒットしたデータ中の識別番号の先頭を格納する
  }
  ptr += names+2; // 次のヒットデータへ
 }
 
 ptr = ptrNames;
 std::string str = "The closest hit names are " ;
 for (j = 0; j < numberOfNames; j++,ptr++) {
  str += ofToString((int)*ptr) + " ";
  selectedList.push_back((int)*ptr);
 }
 std::cout << str << endl;
 
}

