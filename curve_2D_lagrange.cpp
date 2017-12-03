#include "curve_2D_lagrange.h"
#include <vector>
#include <cstdlib>

#include <iostream>

using namespace std;

Vector2f Curve2Dlagrange::aitken_Neville( vector<Vector2f> tab, int n, float x, float frame){
		vector<int> T ;
		for(int k = 0; k < n; k++){
			T.push_back(k);
		}

		for(int j = 0; j < n; j++){
			for (int i = 0; i < n-j; i++){
				tab[i][0] =((T[i] - x)*tab[i+1][0]+ ( x - T[i+j+1])*tab[i][0])/(T[i] - T[i+j+1]);
				tab[i][1] =((T[i] - x)*tab[i+1][1]+ ( x - T[i+j+1])*tab[i][1])/(T[i] - T[i+j+1]);

			}
		}
		Vector2f resu ;
		resu[0] = tab[0][0];
		resu[1] = tab[0][1];


		return resu;
	}


QPainterPath Curve2Dlagrange::path(float frame) {
    QPainterPath p;
    if(nbPts()==0)
      return p;

		vector<Vector2f> tab;
		for(unsigned int i = 0; i < nbPts(); i++ ){
			tab.push_back(evalAnimPt(get(i),frame));
		}

		Vector2f pt = evalAnimPt(get(0),frame);
		p.moveTo(pt[0],pt[1]);
		uint N = 500;

    for(unsigned int i = 0; i < N+1; ++i) {
     	p.lineTo(aitken_Neville(tab, nbPts()-1, float(i)/N, frame)[0],aitken_Neville(tab, nbPts()-1, float(i)/N, frame)[1]);
    }
    return p;
  }
