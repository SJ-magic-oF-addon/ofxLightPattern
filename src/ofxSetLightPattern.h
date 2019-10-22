/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxLightPattern.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class ofx_SET_LIGHTPATTERN{
private:
	static void correct_param(int& NumChs, int& ChId);
public:
	static void setup__Loop_OnOff(ofx_LIGHTPATTERN* LightPattern, int now_ms, double L0, double L1, int T, int NumChs, int ChId);
	static void setup__1way_OnOff(ofx_LIGHTPATTERN* LightPattern, int now_ms, double L0, double L1, int T, int NumChs, int ChId);
	static void setup__Loop_Flash(ofx_LIGHTPATTERN* LightPattern, int now_ms, double L0, double L1, int T, int NumChs, int ChId);
	static void setup__Perlin(ofx_LIGHTPATTERN* LightPattern, int now_ms, double L0, double L1, int T);
	static void setup__Fade(ofx_LIGHTPATTERN* LightPattern, int now_ms, double L0, double L1, int d_a, int d_b);
};
