#ifndef CURVE_1D_HERMITE_H
#define CURVE_1D_HERMITE_H

#include "curve1D.h"
#include <cstdlib>
#include <vector>
#include <math.h>
#include <algorithm>

#include <iostream>
using namespace std;

class Curve1DHermite : public Curve1D {
 public:
 Curve1DHermite(const QString &name) : Curve1D(name) {}
 Curve1DHermite(Curve1D *curve,const QString &name) : Curve1D(curve,name) {}
  
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



  float hermite_init(float t){
    vector<float> X;
    vector<float> Y;
    vector<float> D;
    for(uint idx = 0; idx < nbPts()-1; idx++){
      X.push_back(_points[idx][0]);
      Y.push_back(_points[idx][1]);
      D.push_back(derivate(_points[idx], _points[idx+1]));
    }
    X.push_back(_points[nbPts()-1][0]);
    Y.push_back(_points[nbPts()-1][1]);
    D.push_back(0);


    uint i = 1;
    while ((i < (nbPts()-1)) && (t >= X[i])){
      i++;
    }
    return Y[i-1]*h0((t-X[i-1])/(X[i]-X[i-1])) + Y[i]*h1((t-X[i-1])/(X[i]-X[i-1])) + (X[i]-X[i-1])*(D[i-1]*h2((t-X[i-1])/(X[i]-X[i-1])) + D[i]*h3((t-X[i-1])/(X[i]-X[i-1])));
  }


  QPainterPath path(float xmin,float xmax) {
    QPainterPath p;

    // empty test 
    if(empty()) 
      return p;

    // left part 
    if(xmin<_points[0][0]) {
      p.moveTo(xmin,_points[0][1]);
      p.lineTo(_points[0][0],_points[0][1]);
    } else {
      p.moveTo(_points[0][0],_points[0][1]);
    }

    float min = _points[0][0];
    float max = _points[0][0];

    for (unsigned int i = 1; i<nbPts(); i++){
      if (min > _points[i][0]){
        min = _points[i][0];
      } else if (max < _points[i][0]){
        max = _points[i][0];
      }
    }

    uint N = 500;

    for(unsigned int i = 0; i < N+1; ++i) {
      p.lineTo((float) min+(max-min)*i/N, hermite_init((float) min+(max-min)*i/N));
    }

    // right part 
    if(xmax>_points[nbPts()-1][0]) {
      p.lineTo(xmax,_points[nbPts()-1][1]);
    }

    return p;
  }

  float evalAt(float x) {
    // special cases 
    if(empty()) return 0.0f;
    if(x<=_points[0][0]) return _points[0][1];
    if(x>=_points[nbPts()-1][0]) return _points[nbPts()-1][1];

    return hermite_init(x);
  }
};


class Curve1DHermiteConstructor : public Curve1DConstructor {
 public:
  virtual ~Curve1DHermiteConstructor()                    {}
  virtual const QString type() const                      { return "HermiteCurve";             }
  virtual Curve1D *create(const QString &name)            { return new Curve1DHermite(name);   }
  virtual Curve1D *create(Curve1D *c,const QString &name) { return new Curve1DHermite(c,name); }
};



/*
class Curve1DHermite : public Curve2D {
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

#endif // CURVE_1D_HERMITE_H
