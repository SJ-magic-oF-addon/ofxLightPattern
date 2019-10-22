/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

#include "ofxSetLightPattern.h"

/************************************************************
************************************************************/
class ofApp : public ofBaseApp{
private:
	FILE* fp = nullptr;
	
	enum{
		NUM_LEDS = 3,
	};
	ofx_LIGHTPATTERN LightPattern[NUM_LEDS];
	
	const int MAX_LOG_TIME_MS = 30000;
	bool b_Message = false;
	
	void setup__RandomStrobe_Fall(ofx_LIGHTPATTERN* LightPattern, int now_ms, double L0, double L1);
	
public:
	ofApp();
	~ofApp();
	
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
	
};
