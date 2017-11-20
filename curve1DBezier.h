#ifndef CURVE_1D_BEZIER_H
#define CURVE_1D_BEZIER_H

#include "curve1D.h"


class Curve1DBezier : public Curve1D {
 public:
 Curve1DBezier(const QString &name) : Curve1D(name) {}
 Curve1DBezier(Curve1D *curve,const QString &name) : Curve1D(curve,name) {}

 Vector2f Casteljau2D(int i, int j, float t){
   // Returns the i-th point at the j-th iteration of the algorithm//

   if (j == 0){

     return _points[i];

   } else {

     Vector2f a = Casteljau2D(i, j-1, t);
     Vector2f b = Casteljau2D(i+1, j-1, t);

     Vector2f resu;
     resu[0] = (1-t)*a[0] + t*b[0];
     resu[1] = (1-t)*a[1] + t*b[1];

     return resu;
   }
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

    // draw function
    uint N = 500;
      for (unsigned int i = 0; i < N; i++){
        p.lineTo(Casteljau2D(0, nbPts()-1, (float) i/N)[0], Casteljau2D(0, nbPts()-1, (float) i/N)[1]);
      }

    // right part
    if(xmax>_points[nbPts()-1][0]) {
      p.lineTo(xmax,_points[nbPts()-1][1]);
    }

    return p;
  }


  float Casteljau1D (int i, int j, float x){
    if (j == 0){
      return _points[i][1];

    } else {

      float a = Casteljau1D(i,j-1,x);
      float b = Casteljau1D(i-1,j-1,x);

      float resu = (1-x)*a + x*b;
      return resu;
    }
  }

  float evalAt(float x) {
    // special cases
    if(empty()) return 0.0f;
    if(x<=_points[0][0]) return _points[0][1];
    if(x>=_points[nbPts()-1][0]) return _points[nbPts()-1][1];

    // Bezier Curve
    for(unsigned int i=0;i<nbPts()-1;++i) {
      if(_points[i+1][0]>=x) {
        return Casteljau1D(0, nbPts()-1, x);
      }
    }

    return _points[0][1];
  }
};


class Curve1DBezierConstructor : public Curve1DConstructor {
 public:
  virtual ~Curve1DBezierConstructor()                     {}
  virtual const QString type() const                      { return "BezierCurve";             }
  virtual Curve1D *create(const QString &name)            { return new Curve1DBezier(name);   }
  virtual Curve1D *create(Curve1D *c,const QString &name) { return new Curve1DBezier(c,name); }
};


#endif // CURVE_1D_Bezier_H
