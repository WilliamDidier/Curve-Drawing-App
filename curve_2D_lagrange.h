#ifndef CURVE_2D_lagrange_H
#define CURVE_2D_lagrange_H

#include "curve2D.h"
#include <cstdlib>
#include <vector>

using namespace std;

class Curve2Dlagrange : public Curve2D {
 public:
 Curve2Dlagrange(const QString &name) : Curve2D(name) {}
 Curve2Dlagrange(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
 Vector2f aitken_Neville(vector<Vector2f> tab, int n, float x, float frame);
 QPainterPath path(float frame);
};


class Curve2DlagrangeConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DlagrangeConstructor()                     {}
  virtual const QString type() const                      { return "LagrangeCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2Dlagrange(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2Dlagrange(c,name); }
};


#endif // CURVE_2D_lagrange_H
