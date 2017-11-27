#ifndef CURVE_2D_BSPLINES_H
#define CURVE_2D_BSPLINES_H

#include "curve2D.h"
#include <vector>
#include <cstdlib>

#include <iostream>

using namespace std;

class Curve2DBsplines : public Curve2D {

private:

Vector2f de_boor( vector<Vector2f> D, int k, float t, int p, vector<float> tab){

  vector<Vector2f> d;
  for( int j = 0; j < p+1; j++ ){
    d.push_back(D[j+k-p]);
  }
  for (int r = 1; r< p+1; r++){
    for (int j = p; j > r-1; j--){
      float alpha = (t - tab[j+k-p])/(tab[j+1+k-r]- tab[j+k-p]);
      d[j] = (1-alpha)*d[j-1] + alpha*d[j];
    }

  }
  return d[p];
}

int find_index( vector<float> tab, float t ){

  for (unsigned int i = 0; i<tab.size(); i++){
    if ( t >= tab[i] && t <= tab[i+1] ){
      return i ;
    }

  }
  return 0;
}
public:
Curve2DBsplines(const QString &name) : Curve2D(name) {}
Curve2DBsplines(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}

  QPainterPath path(float frame) {
    QPainterPath p;
    if(nbPts()==0)
      return p;
    unsigned int deg = 3;
    vector<float> tab;
    for (unsigned int i = 0; i< nbPts() + deg ; i++){
      if( i < deg ){
        tab.push_back(0);
      } else if (i >= deg && i < nbPts()+1){
        tab.push_back(i/(deg+nbPts()));
      } else{
        tab.push_back(1);
      }
    }

    vector<Vector2f> D;
    for(unsigned int i = 0; i < nbPts(); i++ ){
      D.push_back(evalAnimPt(get(i),frame));
    }
    Vector2f pt = evalAnimPt(get(0),frame);
    p.moveTo(pt[0],pt[1]);
    uint N = 500;
    for (unsigned int i = 0; i < N; i++){
      float t = i/N;
      int k = find_index(tab, t);
      cout<< k << endl;
      p.lineTo(de_boor(D, k, t, deg, tab)[0],de_boor(D, k, t, deg, tab)[1] );
      }
    return p;
  }
};


class Curve2DBsplinesConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DBsplinesConstructor()                     {}
  virtual const QString type() const                      { return "Bsplinescurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DBsplines(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DBsplines(c,name); }
};


#endif // CURVE_2D_BSPLINES_H
