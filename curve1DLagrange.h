#ifndef CURVE_1D_LAGRANGE_H
#define CURVE_1D_LAGRANGE_H

#include "curve1D.h"

class Curve1DLagrange : public Curve1D {
 public:
 Curve1DLagrange(const QString &name) : Curve1D(name) {}
 Curve1DLagrange(Curve1D *curve,const QString &name) : Curve1D(curve,name) {}
  
  float Curve2Dlagrange::lagrange_newton( vector<float> A, vector<float> X, float x){
  float result = 0;
  float product = 1;
  int size = A.size();
  for( int i = 0; i < size; i++){
    result += A[i]*product;
    product = product*(x-X[i]);

    }
  return result;


}

vector<float> Curve2Dlagrange::coef_newton(){
  vector<float> X;
  vector<float> F;      
  for(uint idx = 0; idx < nbPts(); idx++){
    X.push_back(_points[idx][0]);
    F.push_back(_points[idx][1]);
  }
  vector<float> coef ;
  coef = F;
  for(uint idx = 0; idx < nbPts(); idx++){
    vector<float> coef_bis;
    coef_bis = coef;
    for(uint idx2 = idx + 1; idx2 < nbPts(); idx2++){
      coef[idx2] = (coef_bis[idx2]-coef_bis[idx2-1])/(X[idx2]-X[idx2-idx-1]);
    }
  }
  return coef;
}

float Curve2Dlagrange::lagrange_polynomial(float x){
  vector<float> X;
  for(uint idx = 0; idx < nbPts(); idx++){
    X.push_back(_points[idx][0]);
  }
  float lagX = lagrange_newton(coef_newton(), X, x);
  return lagX;
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
      p.lineTo((float) min+(max-min)*i/N, lagrange_polynomial((float) min+(max-min)*i/N));
    }
    return p;

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

    return lagrange_polynomial(x);
  }
};


class Curve1DLagrangeConstructor : public Curve1DConstructor {
 public:
  virtual ~Curve1DLagrangeConstructor()                     {}
  virtual const QString type() const                      { return "LagrangeCurve";             }
  virtual Curve1D *create(const QString &name)            { return new Curve1DLagrange(name);   }
  virtual Curve1D *create(Curve1D *c,const QString &name) { return new Curve1DLagrange(c,name); }
};


#endif // CURVE_1D_LAGRANGE_H
