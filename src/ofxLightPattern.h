/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class ofx_LIGHTPATTERN{
public:
	struct MIN_MAX_PAIR{
		int min_val;
		int max_val;
		
		MIN_MAX_PAIR()
		: min_val(1000), max_val(2000)
		{
		}
		
		MIN_MAX_PAIR(int _min, int _max)
		: min_val(_min), max_val(_max)
		{
			if(max_val < min_val){
				int temp = min_val;
				min_val = max_val;
				max_val = temp;
			}
		}
	};
	
private:
	enum TYPE{
		TYPE__CONST,
		TYPE__PERLIN,
		TYPE__1WAY,
		TYPE__1TIME,
		TYPE__LOOP,
		TYPE__RAMDOM_TIMING_LOOP,
	};
	
	TYPE Type;
	int t_from_ms;
	int t_from_ms_org;
	
	int d_a, d_b, d_c, d_d;
	
	int T;
	MIN_MAX_PAIR T_from, T_to;
	int d_Transition_T;

	double L0, L1;
	
	double t_PerlinOffset_sec;
	
	
	double update__Const(int now_ms);
	double update__Perlin(int now_ms);
	double update__1way(int now_ms);
	double update__Loop(int now_ms);
	
public:
	ofx_LIGHTPATTERN();
	
	void setup(int now_ms, double _L0);
	void setup(int now_ms, double _L0, double _L1, int _T);
	void setup(int now_ms, double _L0, double _L1, int _d_a, int _d_b);
	void setup(int now_ms, double _L0, double _L1, int _d_a, int _d_b, int _d_c, int _d_d);
	void setup(int now_ms, double _L0, double _L1, int _d_a, int _d_b, int _d_c, int _d_d, int _T);
	void setup(int now_ms, double _L0, double _L1, int _d_b, int _d_c, int _d_d, int _T_from_min, int _T_from_max, int _T_to_min, int _T_to_max, int d_Transition_T);
	void setup(int now_ms, double _L0, double _L1, int _d_b, int _d_c, int _d_d, const MIN_MAX_PAIR& _T_from, const MIN_MAX_PAIR& _T_to, int _d_Transition_T);
	
	double update(int now_ms);
};
