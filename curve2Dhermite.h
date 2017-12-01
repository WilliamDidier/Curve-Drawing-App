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



  Vector2f hermite_init(float frame, float t, uint i){
    Vector2f pt1;
    Vector2f pt2 = evalAnimPt(get(i), frame);
    Vector2f pt3;
    Vector2f D1;
    Vector2f D2;
    if (nbPts() > 1){
      pt1 = evalAnimPt(get(i-1), frame);
      D1[0] = derivate_X(pt1, pt2);
      D1[1] = derivate_Y(pt1, pt2);
      if (i < nbPts()-1){
        pt3 = evalAnimPt(get(i+1), frame);
        D2[0] = derivate_X(pt2, pt3);
        D2[1] = derivate_Y(pt2, pt3);
      } else {
        D2[0] = D1[0];
        D2[1] = D1[1];
      }
    } else {
      pt1[0] = 0;
      pt1[1] = 0;
      D1[0] = 0;
      D1[1] = 0;
      D2[0] = 0;
      D2[1] = 0;
    }
    Vector2f res;
    float tt = pt1[0] + (pt2[0]-pt1[0])*t;
    res[0] = (pt1[0]*h0((tt-pt1[0])/(pt2[0]-pt1[0])) + pt2[0]*h1((tt-pt1[0])/(pt2[0]-pt1[0])) + (pt2[0]-pt1[0])*(D1[0]*h2((tt-pt1[0])/(pt2[0]-pt1[0])) + D2[0]*h3((tt-pt1[0])/(pt2[0]-pt1[0]))));
    res[1] = (pt1[1]*h0((tt-pt1[0])/(pt2[0]-pt1[0])) + pt2[1]*h1((tt-pt1[0])/(pt2[0]-pt1[0])) + (pt2[0]-pt1[0])*(D1[1]*h2((tt-pt1[0])/(pt2[0]-pt1[0])) + D2[1]*h3((tt-pt1[0])/(pt2[0]-pt1[0]))));
    return res;
  }


  QPainterPath path(float frame){
    QPainterPath p;
    if(nbPts()==0)
      return p;
    Vector2f pt = evalAnimPt(get(0), frame);
    p.moveTo(pt[0],pt[1]);
    for (unsigned int ii = 1; ii < nbPts(); ii++){
  		uint N = 100;
      for(unsigned int i = 0; i < N+1; ++i) {
       	p.lineTo(hermite_init(frame, (float) i/N, ii)[0], hermite_init(frame, (float) i/N, ii)[1]);
      }
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
#endif // CURVE_2D_HERMITE_H
