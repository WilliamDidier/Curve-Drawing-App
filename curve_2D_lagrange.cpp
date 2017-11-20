#include "curve_2D_lagrange.h"
#include <vector>

"""
float lagrange_newton( vector<float> A, vector<float> X, float x){
	float result = 0;
	float product = 1;
	int size = A.size();
	for( int i = 0; i < size; i++){
		result += A[i]*product;
		product = product*(x-X[i]);

		}
	return result;


}

vector<float> coef_newton( vector<float> X, vector<float> F ){
	vector<float> coef ;
	coef = F;
	for( int idx = 0; idx<X.size(); idx++){
		vector<float> coef_bis;
		coef_bis = coef;
		for( int idx2 = idx + 1; idx2 < X.size(), idx++){
			coef[idx2] = (coef2[idx2]-coef2[idx2-1])/(X[idx2]-X[idx2-idx-1])
		}

	}
	return coef;
}

float lagrange_polynomial(vector<float> X, vector<float> F, float x){
	float lagX = lagrange_newton(coef_newton(X,F), X, x);
	return lagX;
}

float quadra(float x){
	y = pow(x,2);
	return y ;
}



curve2Dlagrange::QPainterPath path(float frame) {
    QPainterPath p;
    if(nbPts()==0) 
      return p;

    Vector2f pt = evalAnimPt(get(0),frame);

    p.moveTo(pt[0],pt[1]);
    for(unsigned int i=1;i<nbPts();++i) {
      	pt = evalAnimPt(get(i),frame);
      	Vector2f pt_suiv = evalAnimPt(get(0), frame);
    	float dist_x = pt_suiv[0]-pt[0];
    	float step = dist_x/100 ; 

     	p.lineTo(pt[0],pt[1]);
    }
    return p;
  }
  """

