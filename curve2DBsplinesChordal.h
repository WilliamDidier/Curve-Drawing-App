#ifndef CURVE_2D_BSPLINES_CHORDAL_H
#define CURVE_2D_BSPLINES_CHORDAL_H

#include "curve2D.h"
#include <vector>
#include <cstdlib>

#include <iostream>

using namespace std;


class Curve2DBsplinesChordal : public Curve2D {

private:

  float norm(Vector2f point1, Vector2f point2) {
      float new_x = point2[0] - point1[0];
      float new_y = point2[1] - point1[1];
      return (sqrt(pow(new_x, 2) + pow(new_y, 2)));
  }


Vector2f de_boor( vector<Vector2f> D, int k, float t, int p, vector<float> tab){

  vector<Vector2f> d;
  for( int j = 0; j < p+1; j++ ){
    d.push_back(D[j+k-p]);
  }
  for (int r = 1; r< p+1; r++){
    for (int j = p; j > r-1; j--){
      float alpha = (t - tab[j+k-p])/(tab[j+1+k-r]- tab[j+k-p]);
      d[j] = (1.0-alpha)*d[j-1] + alpha*d[j];
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
Curve2DBsplinesChordal(const QString &name) : Curve2D(name) {}
Curve2DBsplinesChordal(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}

  QPainterPath path(float frame) {
    QPainterPath p;
    if(nbPts()==0 ){
      return p;
    }
    p.moveTo(evalAnimPt(get(0),frame)[0],evalAnimPt(get(0),frame)[1]);
    unsigned int deg = 2;


    vector<Vector2f> D;
    for(unsigned int i = 0; i < nbPts(); i++ ){
      D.push_back(evalAnimPt(get(i),frame));
    }

    Vector2f *pts = new Vector2f[nbPts()];
    for (unsigned int i = 0; i<nbPts(); i++) {
      pts[i] = evalAnimPt(get(i), frame);
    }

    float normalization = 0;
    for (unsigned int i = 1; i<nbPts(); i++) {
      normalization += norm(pts[i], pts[i-1]);
    }

    vector<float> chordal_param;
    for (unsigned int i = 0; i<=deg; i++) {
      chordal_param.push_back(norm(pts[1], pts[0])/normalization);
    }
    for (unsigned int i = 1; i<=nbPts(); i++) {
      chordal_param.push_back(chordal_param[i+deg-1] + norm(pts[i], pts[i-1]));
    }
    chordal_param.push_back(chordal_param[nbPts()+deg]);
    chordal_param.push_back(chordal_param[nbPts()+deg]);
    for (unsigned int i = 0; i<=nbPts()+ deg+1; i++) {
      chordal_param[i] = chordal_param[i]/normalization;
    }


    uint N = 500;
    for (unsigned int i = 0; i < N; i++){
      float t = float(i)/N;
      int k = find_index(chordal_param, t);
      p.lineTo(de_boor(D, k, t, deg, chordal_param)[0],de_boor(D, k, t, deg, chordal_param)[1] );
    }
    return p;
  }
};


class Curve2DBsplinesChordalConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DBsplinesChordalConstructor()                     {}
  virtual const QString type() const                      { return "B-splineChordal";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DBsplinesChordal(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DBsplinesChordal(c,name); }
};


#endif // CURVE_2D_BSPLINES_CHORDAL_H
