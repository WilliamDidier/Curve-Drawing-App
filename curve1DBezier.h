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
	/*La fonction  qui trace les courbes roses et violettes : elle peut appeler evalAt*/
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



  float evalAt(float x) {
  	/*La fonction appelée par evalAnimPt dans le cas 2D.
  	Elle renvoie la coordonée y d'un point d'une courbe en x*/
    // special cases
    if(empty()) return 0.0f;
    if(x<=_points[0][0]) return _points[0][1];
    if(x>=_points[nbPts()-1][0]) return _points[nbPts()-1][1];

    uint N = 500;
    float ab = Casteljau2D(0, nbPts()-1, 0)[0];
    int j = 0;
    for (unsigned int i = 1; i < N; i++){
        float ab_tmp = Casteljau2D(0, nbPts()-1, (float) i/N)[0];
        if (abs(ab_tmp-x) < abs(ab-x)){
            ab = ab_tmp;
            j = i;
        }
    }
    return Casteljau2D(0, nbPts()-1, (float) j/N)[1];
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
