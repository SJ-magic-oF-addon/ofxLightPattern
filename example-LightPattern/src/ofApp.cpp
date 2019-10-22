/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp()
{
	fp = fopen("../../../Log.csv", "w");
	if(fp == nullptr){
		printf("Log file open NG\n");
		fflush(stdout);
		std::exit(1);
	}
}

/******************************
******************************/
ofApp::~ofApp()
{
	if(fp)	fclose(fp);
}

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	ofSetWindowTitle("LightPattern");
	
	ofSetWindowShape( 200, 200);
	/*
	ofSetVerticalSync(false);
	ofSetFrameRate(0);
	/*/
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	//*/
	
	ofSetEscapeQuitsApp(false);
	
	/********************
	********************/
	fprintf(fp, ",");
	int now = ofGetElapsedTimeMillis();
	for(int i = 0; i < NUM_LEDS; i++){
		fprintf(fp, "ch_%d,", i);
		
		// ofx_SET_LIGHTPATTERN::setup__Loop_OnOff(&LightPattern[i], now, 0, 1.0, 1000, NUM_LEDS, i);
		ofx_SET_LIGHTPATTERN::setup__1way_OnOff(&LightPattern[i], now, 1.0, 0.0, 2000, NUM_LEDS, i);
		// ofx_SET_LIGHTPATTERN::setup__Loop_Flash(&LightPattern[i], now, 0, 1.0, 1000, NUM_LEDS, i);
		// ofx_SET_LIGHTPATTERN::setup__Perlin(&LightPattern[i], now, 0, 1.0, 3000);
		// ofx_SET_LIGHTPATTERN::setup__Fade(&LightPattern[i], now, 0.2, 0.5, 1000, 2000);
	
		// setup__RandomStrobe_Fall(&LightPattern[i], now, 0, 1.0);
	}
	fprintf(fp, "\n");
}

/******************************
******************************/
void ofApp::setup__RandomStrobe_Fall(ofx_LIGHTPATTERN* LightPattern, int now_ms, double L0, double L1)
{
	/********************
	********************/
	int d_d_ms = 60; // 1 strobeの鋭さ
	int d_Transition_T_ms = 5000; // 遷移時間
	
	/*
	どの時間を見てもX個のLedが光っている(実際はRange内でRandom selectなので、期待値)
		T = d_d_ms * NUM_LEDS / X;
	
	常に、全てのLedが光っている(期待値)
		T = d_d_ms * NUM_LEDS / NUM_LEDS;
		
	0.5個(疎)なら
		T = d_d_ms * NUM_LEDS / 0.5;
	*/
	ofx_LIGHTPATTERN::MIN_MAX_PAIR T_from(d_d_ms * NUM_LEDS/NUM_LEDS, d_d_ms * NUM_LEDS/1);
	ofx_LIGHTPATTERN::MIN_MAX_PAIR T_to(d_d_ms * (NUM_LEDS/0.3), d_d_ms * (NUM_LEDS/0.1));
	
	/* */
	LightPattern->setup(now_ms, L0, L1, 0, 0, d_d_ms, T_from, T_to, d_Transition_T_ms);
}

/******************************
******************************/
void ofApp::update(){
	int now = ofGetElapsedTimeMillis();
	
	if(now < MAX_LOG_TIME_MS){
		fprintf(fp, "%d,", now);
		for(int i = 0; i < NUM_LEDS; i++){
			double Lev = LightPattern[i].update(now);
			fprintf(fp, "%f,", Lev);
		}	
		fprintf(fp, "\n");
	}else if(!b_Message){
		b_Message = true;
		printf("Log file End\n");
		fflush(stdout);
	}
}

/******************************
******************************/
void ofApp::draw(){
	ofBackground(30);
	
	printf("%7.0f\r",ofGetElapsedTimef() );
	fflush(stdout);
}

/******************************
******************************/
void ofApp::keyPressed(int key){

}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
