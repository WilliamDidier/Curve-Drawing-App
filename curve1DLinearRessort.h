#ifndef CURVE_1D_LINEARRESSORT_H
#define CURVE_1D_LINEARRESSORT_H

#include "curve1D.h"
#include <cstdlib>
#include <iostream>

using namespace std;

class Curve1DLinearRessort : public Curve1D {
 public:
 Curve1DLinearRessort(const QString &name) : Curve1D(name) {}
 Curve1DLinearRessort(Curve1D *curve,const QString &name) : Curve1D(curve,name) {}

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

    // draw function
    uint N = 16;
    for (unsigned int i=1;i<nbPts();++i) {
      Vector2f pt_tmp = _points[i-1];
      Vector2f pt_tmp2 = _points[i];
      for (uint j = 0; j < N; j++){
        p.lineTo(pt_tmp[0]+(pt_tmp2[0]-pt_tmp[0])*(1-1/pow(2,j)),pt_tmp2[1]-pow(-1,j)*((pt_tmp2[1]-pt_tmp[1])/pow(2,j)));
      }
      p.lineTo(pt_tmp2[0],pt_tmp2[1]);
    }

    // right part
    if(xmax>_points[nbPts()-1][0]) {
      p.lineTo(xmax,_points[nbPts()-1][1]);
    }

    return p;
  }

  float evalAtLinear(Vector2f pt1, Vector2f pt2, float x) {
    // linear interp
	return pt1[1]+(pt2[1]-pt1[1])*
	  ((x-pt1[0])/(pt2[0]-pt1[0]));
  }


  float evalAt(float x) {
    // special cases
    if(empty()) return 0.0f;
    if(x<=_points[0][0]) return _points[0][1];
    if(x>=_points[nbPts()-1][0]) return _points[nbPts()-1][1];

    uint N = 16;
    Vector2f pt_tmp;
    Vector2f pt_tmp2;
    for(unsigned int i=0;i<nbPts()-1;++i) {
      if(_points[i+1][0]>=x) {
        for (uint j = 0; j < N; j++){
          if (_points[i][0]+(_points[i+1][0]-_points[i][0])*(1-1/pow(2,j+1)) >= x){
            pt_tmp[0] = _points[i][0]+(_points[i+1][0]-_points[i][0])*(1-1/pow(2,j));
            pt_tmp[1] = _points[i+1][1]-pow(-1,j)*((_points[i+1][1]-_points[i][1])/pow(2,j));
            pt_tmp2[0] = _points[i][0]+(_points[i+1][0]-_points[i][0])*(1-1/pow(2,j+1));
            pt_tmp2[1] = _points[i+1][1]+pow(-1,j)*((_points[i+1][1]-_points[i][1])/pow(2,j+1));
            return evalAtLinear(pt_tmp, pt_tmp2, x);
          }
        }
        pt_tmp[0] = _points[i][0]+(_points[i+1][0]-_points[i][0])*(1-1/pow(2,nbPts()-1));
        pt_tmp[1] = _points[i+1][1]-((_points[i+1][1]-_points[i][1])/pow(2,nbPts()-1));
        pt_tmp2 = _points[i+1];
        return evalAtLinear(pt_tmp, pt_tmp2, x);
      }
    }
    return _points[0][1];
  }
};


class Curve1DLinearRessortConstructor : public Curve1DConstructor {
 public:
  virtual ~Curve1DLinearRessortConstructor()              {}
  virtual const QString type() const                      { return "RessortLinearCurve";             }
  virtual Curve1D *create(const QString &name)            { return new Curve1DLinearRessort(name);   }
  virtual Curve1D *create(Curve1D *c,const QString &name) { return new Curve1DLinearRessort(c,name); }
};


#endif // CURVE_1D_LINEARRESSORT_H
