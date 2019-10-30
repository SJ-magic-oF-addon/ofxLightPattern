/************************************************************
note
	L1 < L0 のpatternは、混乱し易い。
	L0 < L1 のpatternを考え、これのLevel反転、とした方が理解し易い。
************************************************************/
#include "ofxSetLightPattern.h"


/************************************************************
************************************************************/

/******************************
******************************/
void ofx_SET_LIGHTPATTERN::correct_param(int& NumChs, int& ChId)
{
	if(NumChs <= 0)		NumChs = 1;
	if(NumChs <= ChId)	ChId = 0;
}

/******************************
parameter
	T	: 1周期 [ms]
******************************/
void ofx_SET_LIGHTPATTERN::setup__Loop_OnOff(ofx_LIGHTPATTERN* LightPattern, int now_ms, double L0, double L1, int T, int NumChs, int ChId)
{
	correct_param(NumChs, ChId);
	
	int Sample_ms = T / (NumChs * 2);
	
	LightPattern->setup(now_ms, L0, L1, Sample_ms * ChId, 0, Sample_ms * NumChs, 0, T);
}

/******************************
parameter
	T		: 全chが L1 に渡り終える時間
	L0/L1	: ON -> OFF の時は L0 = 1, L1 = 0.
			  OFF -> ON の時は L0 = 0, L1 = 1.
******************************/
void ofx_SET_LIGHTPATTERN::setup__1way_OnOff(ofx_LIGHTPATTERN* LightPattern, int now_ms, double L0, double L1, int T, int NumChs, int ChId)
{
	correct_param(NumChs, ChId);
	
	int Sample_ms = T / NumChs;
	
	LightPattern->setup(now_ms, L0, L1, Sample_ms * (ChId + 1), 0);
}

/******************************
******************************/
void ofx_SET_LIGHTPATTERN::setup__Loop_Flash(ofx_LIGHTPATTERN* LightPattern, int now_ms, double L0, double L1, int T, int NumChs, int ChId)
{
	correct_param(NumChs, ChId);
	
	int Sample_ms = T / (NumChs * 1);
	
	LightPattern->setup(now_ms, L0, L1, Sample_ms * ChId, 0, 0, Sample_ms, T);
}

/******************************
******************************/
void ofx_SET_LIGHTPATTERN::setup__Perlin(ofx_LIGHTPATTERN* LightPattern, int now_ms, double L0, double L1, int T)
{
	LightPattern->setup(now_ms, L0, L1, T);
}

/******************************
******************************/
void ofx_SET_LIGHTPATTERN::setup__Fade(ofx_LIGHTPATTERN* LightPattern, int now_ms, double L0, double L1, int d_a, int d_b)
{
	LightPattern->setup(now_ms, L0, L1, d_a, d_b);
}

