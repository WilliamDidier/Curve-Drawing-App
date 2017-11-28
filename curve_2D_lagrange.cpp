#include "curve_2D_lagrange.h"
#include <vector>
#include <cstdlib>

#include <iostream>

using namespace std;

float Curve2Dlagrange::lagrange_newton( vector<float> A, vector<float> X, float x){
	float result = 0;
	float product = 1;
	int size = A.size();
	for( int i = 0; i < size; i++){
		result += A[i]*product;
		product = product*(x-X[i]);

		}
	return result;


}

vector<float> Curve2Dlagrange::coef_newton(float frame){
	vector<float> X;
	vector<float> F;      
	for(uint idx = 0; idx < nbPts(); idx++){
		Vector2f pt = evalAnimPt(get(idx), frame);
		X.push_back(pt[0]);
		F.push_back(pt[1]);
	}
	vector<float> coef ;
	coef = F;
	for(uint idx = 0; idx < nbPts(); idx++){
		vector<float> coef_bis;
		coef_bis = coef;
		for(uint idx2 = idx + 1; idx2 < nbPts(); idx2++){
			coef[idx2] = (coef_bis[idx2]-coef_bis[idx2-1])/(X[idx2]-X[idx2-idx-1]);
		}
	}
	return coef;
}

float Curve2Dlagrange::lagrange_polynomial(float frame, float x){
	vector<float> X;
	for(uint idx = 0; idx < nbPts(); idx++){
		Vector2f pt = evalAnimPt(get(idx), frame);
		X.push_back(pt[0]);
	}
	float lagX = lagrange_newton(coef_newton(frame), X, x);
	return lagX;
}

QPainterPath Curve2Dlagrange::path(float frame) {
    QPainterPath p;
    if(nbPts()==0)
      return p;

		Vector2f pt = evalAnimPt(get(0),frame);
		p.moveTo(pt[0],pt[1]);

		float min = pt[0];
		float max = pt[0];

		for (unsigned int i = 1; i<nbPts(); i++){
			pt = evalAnimPt(get(i), frame);
			if (min > pt[0]){
				min = pt[0];
			} else if (max < pt[0]){
				max = pt[0];
			}
		}

		uint N = 500;

    for(unsigned int i = 0; i < N+1; ++i) {
     	p.lineTo((float) min+(max-min)*i/N, lagrange_polynomial(frame, (float) min+(max-min)*i/N));
    }
    return p;
  }
