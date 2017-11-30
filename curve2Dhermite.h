#ifndef CURVE_2D_HERMITE_H
#define CURVE_2D_HERMITE_H

#include "curve2D.h"
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

class Curve2DHermite : public Curve2D {
 public:
 Curve2DHermite(const QString &name) : Curve2D(name) {}
 Curve2DHermite(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}

  float h0(float t){
    float res = 2.0*pow(t,3.0)-3*pow(t,2.0)+1.0;
    return res;
  }

  float h1(float t){
    float res = -2.0*pow(t,3.0)+3.0*pow(t,2.0);
    return res;
  }

  float h2(float t){
    float res = pow(t,3.0)-2.0*pow(t,2.0)+t;
    return res;
  }

  float h3(float t){
    float res = pow(t,3.0)-pow(t,2.0);
    return res;
  }

  float derivate_X(Vector2f pt1, Vector2f pt2 ){
    float res = (pt2[1]-pt1[1])/(pt2[0]-pt1[0]);
    return res;
  }

  float derivate_Y(Vector2f pt1, Vector2f pt2 ){
    float res = (pt2[0]-pt1[0])/(pt2[1]-pt1[1]);
    return res;
  }



  vector<float> hermite_init(float frame, float t){
    vector<float> X;
    vector<float> X_prime;
    vector<float> Y;
    vector<float> Y_prime;
    vector<float> D_X;
    vector<float> D_Y;
    vector<float> res;
    for(uint idx = 0; idx < nbPts()-1; idx++){
      Vector2f pt = evalAnimPt(get(idx), frame);
      Vector2f pt2 = evalAnimPt(get(idx+1), frame);
      X.push_back(pt[0]);
      X_prime.push_back(pt2[0]);
      Y.push_back(pt[1]);
      Y_prime.push_back(pt2[1]);
      D_X.push_back(derivate_X(pt, pt2));
      D_Y.push_back(derivate_Y(pt, pt2));
    }
    Vector2f pt = evalAnimPt(get(nbPts()-1), frame);
    X.push_back(pt[0]);
    X_prime.push_back(0);
    Y.push_back(pt[1]);
    Y_prime.push_back(0);
    D_X.push_back(0);
    D_Y.push_back(0);

  //  sort(X.begin(), X.end(), tri_X);
    //sort(Y.begin(), Y.end(), tri_X);
    //sort(D.begin(), D.end(), tri_X);


    uint i = 1;
    while ((i < (nbPts()-1)) && (t >= X[i])){
      i++;
    }
    cout<< i << endl;
    res.push_back(X_prime[i-1]*h0((t-X[i-1])/(X[i]-X[i-1])) + X_prime[i]*h1((t-X[i-1])/(X[i]-X[i-1])) + (X[i]-X[i-1])*(D_X[i-1]*h2((t-X[i-1])/(X[i]-X[i-1])) + D_X[i]*h3((t-X[i-1])/(X[i]-X[i-1]))));
    res.push_back(Y_prime[i-1]*h0((t-Y[i-1])/(Y[i]-Y[i-1])) + Y_prime[i]*h1((t-Y[i-1])/(Y[i]-Y[i-1])) + (Y[i]-Y[i-1])*(D_Y[i-1]*h2((t-Y[i-1])/(Y[i]-Y[i-1])) + D_Y[i]*h3((t-Y[i-1])/(Y[i]-Y[i-1]))));
    return res;
  }


  QPainterPath path(float frame) {
    QPainterPath p;
    if(nbPts()==0)
      return p;
    Vector2f pt = evalAnimPt(get(0),frame);
    float min = pt[0];
    float max = pt[0];
		p.moveTo(pt[0],pt[1]);
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
     	p.lineTo(hermite_init(frame, (float) min+(max-min)*i/N )[0], hermite_init(frame, (float) min+(max-min)*i/N)[1]);
    }
    return p;
  }
};


class Curve2DHermiteConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DHermiteConstructor()                    {}
  virtual const QString type() const                      { return "HermiteCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DHermite(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DHermite(c,name); }
};
/*
class Curve2DHermite : public Curve2D {
 public:
 Curve2DHermite(const QString &name) : Curve2D(name) {}
 Curve2DHermite(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}

  float h0(float t){
    float res = 2.0*pow(t,3.0)-3*pow(t,2.0)+1.0;
    return res;
  }

  float h1(float t){
    float res = -2.0*pow(t,3.0)+3.0*pow(t,2.0);
    return res;
  }

  float h2(float t){
    float res = pow(t,3.0)-2.0*pow(t,2.0)+t;
    return res;
  }

  float h3(float t){
    float res = pow(t,3.0)-pow(t,2.0);
    return res;
  }

  float derivate(Vector2f p1, Vector2f p2){
    float res = (p2[1]-p1[1])/(p2[0]-p1[0]);
    return res;
  }



  float hermite_init(float frame, float t){
    vector<float> X;
    vector<float> Y;
    vector<float> D;
    for(uint idx = 0; idx < nbPts()-1; idx++){
      Vector2f pt = evalAnimPt(get(idx), frame);
      Vector2f pt2 = evalAnimPt(get(idx+1), frame);
      X.push_back(pt[0]);
      Y.push_back(pt[1]);
      D.push_back(derivate(pt, pt2));
    }
    Vector2f pt = evalAnimPt(get(nbPts()-1), frame);
    X.push_back(pt[0]);
    Y.push_back(pt[1]);
    D.push_back(0);

  //  sort(X.begin(), X.end(), tri_X);
    //sort(Y.begin(), Y.end(), tri_X);
    //sort(D.begin(), D.end(), tri_X);


    uint i = 1;
    while ((i < (nbPts()-1)) && (t >= X[i])){
      i++;
    }
    return Y[i-1]*h0((t-X[i-1])/(X[i]-X[i-1])) + Y[i]*h1((t-X[i-1])/(X[i]-X[i-1])) + (X[i]-X[i-1])*(D[i-1]*h2((t-X[i-1])/(X[i]-X[i-1])) + D[i]*h3((t-X[i-1])/(X[i]-X[i-1])));
  }


  QPainterPath path(float frame) {
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
       	p.lineTo((float) min+(max-min)*i/N, hermite_init(frame, (float) min+(max-min)*i/N));
      }
      return p;
    }
};


class Curve2DHermiteConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DHermiteConstructor()                    {}
  virtual const QString type() const                      { return "HermiteCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DHermite(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DHermite(c,name); }
};
*/
#endif // CURVE_2D_HERMITE_H
