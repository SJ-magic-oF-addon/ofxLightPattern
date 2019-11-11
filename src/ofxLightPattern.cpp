/************************************************************
************************************************************/
#include "ofxLightPattern.h"

/************************************************************
************************************************************/

/******************************
******************************/
ofx_LIGHTPATTERN::ofx_LIGHTPATTERN()
: Type(TYPE__CONST)
, t_from_ms(0)
, t_from_ms_org(0)
, d_a(0)
, d_b(0)
, d_c(0)
, d_d(0)
, T(1000)
, d_Transition_T(1000)
, t_PerlinOffset_sec(0.12)
, L0(0.0)
, L1(1.0)
{
}

/******************************
******************************/
void ofx_LIGHTPATTERN::setup(int now_ms, double _L0)
{
	Type = TYPE__CONST;
	
	L0 = _L0;
	
	t_from_ms = now_ms;
}

/******************************
******************************/
void ofx_LIGHTPATTERN::setup(int now_ms, double _L0, double _L1, int _T)
{
	Type = TYPE__PERLIN;
	
	L0 = _L0;
	L1 = _L1;
	T = _T;
	
	t_PerlinOffset_sec = ofRandom(0, 1000);
	
	t_from_ms = now_ms;	
}

/******************************
******************************/
void ofx_LIGHTPATTERN::setup(int now_ms, double _L0, double _L1, int _d_a, int _d_b)
{
	Type = TYPE__1WAY;
	
	L0 = _L0;
	L1 = _L1;
	
	d_a = _d_a;
	d_b = _d_b;
	
	t_from_ms = now_ms;
}

/******************************
******************************/
void ofx_LIGHTPATTERN::setup(int now_ms, double _L0, double _L1, int _d_a, int _d_b, int _d_c, int _d_d)
{
	Type = TYPE__1TIME;
	
	L0 = _L0;
	L1 = _L1;
	
	d_a = _d_a;
	d_b = _d_b;
	d_c = _d_c;
	d_d = _d_d;
	
	t_from_ms = now_ms;
}

/******************************
******************************/
void ofx_LIGHTPATTERN::setup(int now_ms, double _L0, double _L1, int _d_a, int _d_b, int _d_c, int _d_d, int _T, bool _b_Keep_T)
{
	Type = TYPE__LOOP;
	
	L0 = _L0;
	L1 = _L1;
	
	d_a = _d_a;
	d_b = _d_b;
	d_c = _d_c;
	d_d = _d_d;
	
	T = _T;
	b_Keep_T = _b_Keep_T;
	
	t_from_ms = now_ms;
}

/******************************
******************************/
void ofx_LIGHTPATTERN::setup(int now_ms, double _L0, double _L1, int _d_b, int _d_c, int _d_d, int _T_from_min, int _T_from_max, int _T_to_min, int _T_to_max, int _d_Transition_T)
{
	MIN_MAX_PAIR _T_from(_T_from_min, _T_from_max);
	MIN_MAX_PAIR _T_to(_T_to_min, _T_to_max);
	
	setup(now_ms, _L0, _L1, _d_b, _d_c, _d_d, _T_from, _T_to, _d_Transition_T);
}

/******************************
******************************/
void ofx_LIGHTPATTERN::setup(int now_ms, double _L0, double _L1, int _d_b, int _d_c, int _d_d, const MIN_MAX_PAIR& _T_from, const MIN_MAX_PAIR& _T_to, int _d_Transition_T)
{
	Type = TYPE__RAMDOM_TIMING_LOOP;
	
	L0 = _L0;
	L1 = _L1;
	
	d_a = ofRandom(0, _T_from.get_max()); // 先頭ずらす. 最初の t_from_ms 更新時、d_a = 0とする(update_Loop()).
	// d_a = 0;
	d_b = _d_b;
	d_c = _d_c;
	d_d = _d_d;
	
	T = ofRandom(_T_from.get_min(), _T_from.get_max());
	T_from = _T_from;
	T_to = _T_to;
	b_Keep_T = false;

	d_Transition_T = _d_Transition_T;
	
	t_from_ms = now_ms;
	t_from_ms_org = now_ms;
}

/******************************
******************************/
void ofx_LIGHTPATTERN::setup__Loop_Sin(int now_ms, double _L0, double _L1, int _T, double phase_deg)
{
	Type = TYPE__LOOP_SIN;
	
	L0 = _L0;
	L1 = _L1;
	
	T = _T;
	
	t_phase = int(T/360.0 * phase_deg);
	
	t_from_ms = now_ms;
	t_from_ms_org = now_ms;
}

/******************************
******************************/
double ofx_LIGHTPATTERN::update(int now_ms)
{
	double ret = 0;
	switch(Type){
		case TYPE__CONST:
			ret = update__Const(now_ms);
			break;
		case TYPE__PERLIN:
			ret = update__Perlin(now_ms);
			break;
		case TYPE__1WAY:
			ret = update__1way(now_ms);
			break;
		case TYPE__1TIME:
		case TYPE__LOOP:
		case TYPE__RAMDOM_TIMING_LOOP:
			ret = update__Loop(now_ms);
			break;
		case TYPE__LOOP_SIN:
			ret = update__Loop_Sin(now_ms);
			break;
	}
	
	return ret;
}

/******************************
******************************/
double ofx_LIGHTPATTERN::update__Const(int now_ms)
{
	return L0;
}

/******************************
******************************/
double ofx_LIGHTPATTERN::update__Perlin(int now_ms)
{
	/********************
	********************/
	double dt = (double(now_ms) - t_from_ms) / 1000; // secで計算. perlinはintでalways 0.5
	if(dt < 0) return 0;
	
	/********************
	********************/
	double _T = double(T) / 1000; // secで計算.
	return ofMap( ofNoise(double(dt)/_T +  t_PerlinOffset_sec), 0, 1, L0, L1, true );
}

/******************************
******************************/
double ofx_LIGHTPATTERN::update__1way(int now_ms)
{
	/********************
	********************/
	int dt = now_ms - t_from_ms;
	if(dt < 0) return 0;
	
	/********************
	********************/
	if(dt < d_a){
		return L0;
		
	}else if(dt < d_a + d_b){
		if(d_b == 0) { printf("Error in %s:%d\n", __FILE__, __LINE__); std::exit(1); }	// d_b == 0 はokだが、その時は、ここに入ってこないはず.
		
		double tan = (L1 - L0) / d_b;
		return tan * (dt - d_a) + L0;
		
	}else{
		return L1;
		
	}
}

/******************************
******************************/
double ofx_LIGHTPATTERN::update__Loop(int now_ms)
{
	/********************
	********************/
	int dt = now_ms - t_from_ms;
	if(dt < 0) return 0;
	
	/********************
	********************/
	if(T < dt){
		if(Type == TYPE__1TIME){
			// no Reset.
		}else if(Type == TYPE__LOOP){
			/********************
			Tを確実に守りたいなら b_Keep_T = true;
			ただし、速いpatternでsamplingの関係からTop Levelが出ないことがある。
			その時は、b_Keep_T = false; とする。
			********************/			
			if(b_Keep_T)	t_from_ms = now_ms - (dt - T);
			else			t_from_ms = now_ms;
			
			dt = now_ms - t_from_ms;
			
		}else if(Type == TYPE__RAMDOM_TIMING_LOOP){
			/* */
			// t_from_ms = now_ms - (dt - T);
			t_from_ms = now_ms; // そもそもRandomなので、Tにシビアである必要なし。Top Levelが出る方が大事。
			
			dt = now_ms - t_from_ms;
			
			// 2回目以降は、Tの揺れ のみで.
			// せっかく t_from_ms = now_ms; としても、d_a != 0 だとstart 時間がズレ、samplingの関係でTop Levelが出ないことがあるので(速いStrobeなど)
			d_a = 0;
			
			/* */
			double ratio = (double(now_ms) - t_from_ms_org) / d_Transition_T;
			int T_min = (int)ofMap(ratio, 0.0, 1.0, T_from.get_min(), T_to.get_min(), true);
			int T_max = (int)ofMap(ratio, 0.0, 1.0, T_from.get_max(), T_to.get_max(), true);
			
			T = ofRandom(T_min, T_max);
		}
	}
	
	/********************
	********************/
	if(dt < d_a){
		return L0;
		
	}else if(dt < d_a + d_b){
		if(d_b == 0) { printf("Error in %s:%d\n", __FILE__, __LINE__); std::exit(1); }	// d_b == 0 はokだが、その時は、ここに入ってこないはず.
		
		double tan = (L1 - L0) / d_b;
		return tan * (dt - d_a) + L0;
		
	}else if(dt < d_a + d_b + d_c){
		return L1;
		
	}else if(dt < d_a + d_b + d_c + d_d){
		if(d_d == 0) { printf("Error in %s:%d\n", __FILE__, __LINE__); std::exit(1); }	// d_d == 0 はokだが、その時は、ここに入ってこないはず.
		
		double tan = (L0 - L1) / d_d;
		return tan * (dt - (d_a + d_b + d_c)) + L1;
		
	}else{
		return L0;
		
	}
}

/******************************
******************************/
double ofx_LIGHTPATTERN::update__Loop_Sin(int now_ms)
{
	/********************
	********************/
	int dt = now_ms - t_from_ms;
	if(dt < 0) return 0;
	
	/********************
	********************/
	if(T < dt){
		t_from_ms = now_ms - (dt - T);
		dt = now_ms - t_from_ms;		
	}
	
	return ofMap(sin(2 * PI * (dt - t_phase) / T), -1, 1, L0, L1);
}

