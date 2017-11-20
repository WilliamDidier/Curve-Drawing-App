#ifndef CURVE_2D_lagrange_H
#define CURVE_2D_lagrange_H

#include "curve2D.h"

class Curve2Dlagrange : public Curve2D {
 public:
 Curve2Dlagrange(const QString &name) : Curve2D(name) {}
 Curve2Dlagrange(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
 QPainterPath path(float frame);
};


class Curve2DlagrangeConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DlagrangeConstructor()                     {}
  virtual const QString type() const                      { return "lagrangeCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2Dlagrange(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2Dlagrange(c,name); }
};


#endif // CURVE_2D_lagrange_H
