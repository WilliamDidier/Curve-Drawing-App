#ifndef CURVE_1D_Bsplines_H
#define CURVE_1D_Bsplines_H

#include "curve1D.h"
#include "curve2D.h"
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

class Curve1DBsplines : public Curve1D {
 public:
 Curve1DBsplines(const QString &name) : Curve1D(name) {}
 Curve1DBsplines(Curve1D *curve,const QString &name) : Curve1D(curve,name) {}

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

 vector<float> create_tab_nodes(){
     unsigned int deg = 3;
     vector<float> tab;
     for (unsigned int i = 0; i < nbPts() + deg; i++){
       if( i <= deg ){
         tab.push_back(0);
       } else if (i >= deg && i <= nbPts()){
         tab.push_back(float(i)/(nbPts()));
       } else{
         tab.push_back(1);
       }
     }
     return tab;
   }

vector<Vector2f> create_tab_point(){
  vector<Vector2f> D;
  for(unsigned int i = 0; i < nbPts(); i++ ){
    D.push_back(_points[i]);
  }
  return D;
}
  QPainterPath path(float xmin,float xmax) {
    QPainterPath p;
    unsigned int deg = 3;
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

    vector<float> tab  = create_tab_nodes();
    vector<Vector2f> D = create_tab_point();


    uint N = 500;
    for (unsigned int i = 0; i < N; i++){
      float t = float(i)/N;
      int k = find_index(tab, t);
      p.lineTo(de_boor(D, k, t, deg, tab)[0],de_boor(D, k, t, deg, tab)[1] );
    }

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

    // Bsplines interp
    uint N = 500;
    unsigned int deg = 2;
    vector<float> tab  = create_tab_nodes();
    vector<Vector2f> D = create_tab_point();
    float ab = de_boor(D, 0, 0, deg, tab)[0];
    int j = 0;
    for(unsigned int i=0;i< N;++i) {
      float t = float(i)/N;
      int k = find_index(tab, t);
      float ab_tmp = de_boor(D, k, t, deg, tab)[0];
      if (abs(ab_tmp-x) < abs(ab-x)){
          ab = ab_tmp;
          j = i;
      }
    }
    float t = float(j)/N;
    int k = find_index(tab, t);
    return de_boor(D, k, t, deg, tab)[1];
  }
};


class Curve1DBsplinesConstructor : public Curve1DConstructor {
 public:
  virtual ~Curve1DBsplinesConstructor()                     {}
  virtual const QString type() const                      { return "BsplinesCurve";             }
  virtual Curve1D *create(const QString &name)            { return new Curve1DBsplines(name);   }
  virtual Curve1D *create(Curve1D *c,const QString &name) { return new Curve1DBsplines(c,name); }
};


#endif // CURVE_1D_Bsplines_H
