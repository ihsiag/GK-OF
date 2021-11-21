# 00_myOf

00-version:of_v0.11.2_vs2017_release

01-Add projectGenerator shortcut-link to your startup menu
[C:\Users\---\AppData\Roaming\Microsoft\Windows\Start Menu\Programs]

02-You should include ofxGKUtils.h into your project when you use and run a program in this repository.


03-ADDONS LIST that You have to download and put into addon folder manually.
- ofxBullet
- ofxGuiExtended
- ofxBox2D
- ofxPostProcessing


04-CHANGES LIST that you have to modify your exsiting addons by yourself

//--------------------------------------------------------------------
- To ofEasyCam.h
public:
/// ADDED BY GAISHI KUDO
	void setScrollFlip(const bool& _bool);

private:
/// ADDED BY GAISHI KUDO
	int IsScrollFlipped; //-1 = true


- To ofEasyCam.cpp
constructor(){
    /// ADDED BY GAISHI KUDO
	IsScrollFlipped = 1; //false
}
void ofEasyCam::setScrollFlip(const bool& _bool) {
	if (_bool)IsScrollFlipped = -1;
	if (!_bool)IsScrollFlipped = 1;
}
inside void ofEasyCam::mouseScrolled(ofMouseEventArgs & mouse):
BEFORE: translate.z = mouse.scrollY * 30 * sensitivityTranslate.z * (getDistance() + std::numeric_limits<float>::epsilon())/ area.height;
AFTER: translate.z = IsScrollFlipped * mouse.scrollY * 30 * sensitivityTranslate.z * (getDistance() + std::numeric_limits<float>::epsilon())/ area.height;

inside void ofEasyCam::mouseReleased(ofMouseEventArgs & mouse):
BEFORE: reset();
AFTER: //reset();

//-------------------------------------------------------------------- 
