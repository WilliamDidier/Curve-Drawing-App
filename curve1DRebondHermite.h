#ifndef CURVE_1D_HERMITEREBOND_H
#define CURVE_1D_HERMITEREBOND_H

#include "curve1D.h"
#include <cstdlib>
#include <vector>
#include <math.h>
#include <algorithm>

#include <iostream>
using namespace std;

class Curve1DRebondHermite : public Curve1D {
 public:
 Curve1DRebondHermite(const QString &name) : Curve1D(name) {}
 Curve1DRebondHermite(Curve1D *curve,const QString &name) : Curve1D(curve,name) {}

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
    uint R = 8;
    Vector2f pt_tmp;
    Vector2f pt_tmp2;
    for(uint i = 0; i < nbPts()-1; i++){
      for (uint j = 0; j < R; j++){
        pt_tmp[0] = _points[i][0]+(_points[i+1][0]-_points[i][0])*(1-1/pow(2,j));
        pt_tmp[1] = _points[i+1][1]-(1-pow(-1,j+1))*((_points[i+1][1]-_points[i][1])/pow(2,j+1));
        pt_tmp2[0] = _points[i][0]+(_points[i+1][0]-_points[i][0])*(1-1/pow(2,j+1));
        pt_tmp2[1] = _points[i+1][1]-(1-pow(-1,j+2))*((_points[i+1][1]-_points[i][1])/pow(2,j+2));
        X.push_back(pt_tmp[0]);
        Y.push_back(pt_tmp[1]);
        D.push_back(derivate(pt_tmp, pt_tmp2));
      }
      pt_tmp[0] = _points[i][0]+(_points[i+1][0]-_points[i][0])*(1-1/pow(2,nbPts()-1));
      pt_tmp[1] = _points[i+1][1]-(1-pow(-1,nbPts()))*((_points[i+1][1]-_points[i][1])/pow(2,nbPts()));
      pt_tmp2 = _points[i+1];
      X.push_back(pt_tmp[0]);
      Y.push_back(pt_tmp[1]);
      D.push_back(derivate(pt_tmp, pt_tmp2));
    }
    X.push_back(_points[nbPts()-1][0]);
    Y.push_back(_points[nbPts()-1][1]);
    D.push_back(0);


    uint i = 1;
    while ((i < R*(nbPts()-1)) && (t >= X[i])){
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

    for (unsigned int i = 1; i < nbPts(); i++){
      if (min > _points[i][0]){
        min = _points[i][0];
      } else if (max < _points[i][0]){
        max = _points[i][0];
      }
    }

    uint N = 200;

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
    if(x>=_points[(nbPts()-1)][0]) return _points[(nbPts()-1)][1];

    return hermite_init(x);
  }
};


class Curve1DRebondHermiteConstructor : public Curve1DConstructor {
 public:
  virtual ~Curve1DRebondHermiteConstructor()                    {}
  virtual const QString type() const                      { return "RebondHermiteCurve";             }
  virtual Curve1D *create(const QString &name)            { return new Curve1DRebondHermite(name);   }
  virtual Curve1D *create(Curve1D *c,const QString &name) { return new Curve1DRebondHermite(c,name); }
};



#endif // CURVE_1D_HERMITEREBOND_H
