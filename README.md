# 00_myOf

You should include ClassMyFunctions.h when you run a program in this repository


ADDONS LIST that I added myself
- ofxBullet


CHANGES that I did to the exsiting addons

//--------------------------------------------------------------------
-To ofEasyCam.h
public:
/// ADDED BY GAISHI KUDO
	void setScrollFlip(const bool& _bool);

private:
/// ADDED BY GAISHI KUDO
	int IsScrollFlipped; //-1 = true


-To ofEasyCam.cpp
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
