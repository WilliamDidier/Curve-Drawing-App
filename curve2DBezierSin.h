#ifndef CURVE_2D_BEZIER_SIN_H
#define CURVE_2D_BEZIER_SIN_H

#include "curve2D.h"
#include "math.h"
#include <iostream>

class Curve2DBezierSin : public Curve2D {

private:

Vector2f pij(int i, int j, float t, float frame){
  // Returns the i-th point at the j-th iteration of the algorithm//

  if (j == 0){

    return evalAnimPt(get(i), frame);

  } else {

    Vector2f a = pij(i, j-1, t, frame);
    Vector2f b = pij(i+1, j-1, t, frame);

    Vector2f resu;
    resu[0] = (1-t)*a[0] + t*b[0];
    resu[1] = (1-t)*a[1] + t*b[1];
    std::cout << sin((1-t)*a[1] + t*b[1]) << std::endl;

    return resu;

  }
}

public:
Curve2DBezierSin(const QString &name) : Curve2D(name) {}
Curve2DBezierSin(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}

  QPainterPath path(float frame) {
    QPainterPath p;
    if(nbPts()==0)
      return p;

    Vector2f pt = evalAnimPt(get(0),frame);

    p.moveTo(pt[0],pt[0] + sin(pt[1]));

    uint N = 500;
    p.lineTo(pij(0, nbPts()-1, 0, frame)[0], pij(0, nbPts()-1, 0, frame)[1]);
      for (unsigned int i = 0; i < N; i++){
        p.lineTo(pij(0, nbPts()-1, (float) i/N, frame)[0], pij(0, nbPts()-1, (float) i/N, frame)[0] + 10 * sin(pij(0, nbPts()-1, (float) i/N, frame)[1]));
      }
    return p;
  }
};


class Curve2DBezierSinConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DBezierSinConstructor()                     {}
  virtual const QString type() const                      { return "BezierCurveSin";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DBezierSin(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DBezierSin(c,name); }
};


#endif // CURVE_2D_BEZIER_SIN_H
