#ifndef CURVE_2D_BEZIER_H
#define CURVE_2D_BEZIER_H

#include "curve2D.h"

class Curve2DBezier : public Curve2D {

private:

Vector2f pij(int i, int j, float t, float frame){

  if (j == 0){

    return evalAnimPt(get(i), frame);

  } else {

    Vector2f a = pij(i, j-1, t, frame);
    Vector2f b = pij(i+1, j-1, t, frame);  

    Vector2f resu;
    resu[0] = (1-t)*a[0] + t*b[0];
    resu[1] = (1-t)*a[1] + t*b[1];

    return resu;

  }
}

public:
Curve2DBezier(const QString &name) : Curve2D(name) {}
Curve2DBezier(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
  
  QPainterPath path(float frame) {
    QPainterPath p;
    if(nbPts()==0) 
      return p;

    Vector2f pt = evalAnimPt(get(0),frame);

    p.moveTo(pt[0],pt[1]);

    uint N = 500;
      for (unsigned int i = 0; i < N; i++){
        p.lineTo(pij(0, nbPts()-1, (float) i/N, frame)[0], pij(0, nbPts()-1, (float) i/N, frame)[1]);
      }
    return p;
  }
};


class Curve2DBezierConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DBezierConstructor()                     {}
  virtual const QString type() const                      { return "BezierCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DBezier(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DBezier(c,name); }
};


#endif // CURVE_2D_BEZIER_H