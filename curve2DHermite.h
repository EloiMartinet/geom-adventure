#ifndef CURVE_2D_HERMITE_H
#define CURVE_2D_HERMITE_H

#include "curve2D.h"
#include <vector>
#include <iostream>

using namespace std;

class Curve2DHermite : public Curve2D {
 public:
 Curve2DHermite(const QString &name) : Curve2D(name) {}
 Curve2DHermite(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}

vector< vector <double> > hermiteInter(vector< vector<double> > const checkPoint, double h)
{
    unsigned int N = (int)(1/h);
    vector< vector<double> > H(N);
    vector< vector<double> > li(N, (double ) 1);
    //vector<double> dy(1,N);
    vector<double> x(N);
    vector<double> y(N);
    double a = (checkPoint[1][1] - checkPoint[0][1])/(checkPoint[1][0] - checkPoint[0][0]);
    double b = checkPoint[0][1] - a * checkPoint[0][0];
    x[0] = checkPoint[0][0];
    y[0] = a*x[0] + b;
    for (unsigned int i = 1; i < N; i++) {
      x[i] = x[i-1] + i/h;
      y[i] = a*x[i] + b;
    }
    /*
    dy[0] = (y[1] - y[0])/h;
    for (unsigned int i = 1; i < N-1; i++) {
      dy[i] = (y[i+1] - y[i-1])/(2*h);
    }
    dy[-1] = (y[-1] - y[-2])/h;
    */
    for (unsigned int i = 0; i < N; i++) {
      double u = checkPoint[0][0];
      double dl = 0;
      for (unsigned int j = 0; j < N; j++) {
        if (j != i) {
          dl += 1/(x[j] - x[i]);
          li[i][j] = li[i][j] * (u - x[j])/(x[j] - x[i]);
        }
      }
      vector<double> l2 = li[i]**(2);
      H[i][0] = x[i];
      vector<double> tmp1(N, (double) (u - x[i]) * a);
      vector<double> tmp2(N, (double) (1 - 2*(u - x[i])*dl) * y[i]);
      for
      H[i][1] = l2 * tmp2;
      H[i][1] += l2 * tmp1;
    }
    return H;
}

  QPainterPath path(float frame) {
    QPainterPath p;
    double N(100);
    vector< vector<double> > checkPoint(nbPts());
    vector< vector<double> >  H(2);
    if(nbPts()==0)
      return p;

    Vector2f pt = evalAnimPt(get(0),frame);

    p.moveTo(pt[0],pt[1]);
    checkPoint[0].push_back(pt[0]);
    checkPoint[0].push_back(pt[1]);
    for(unsigned int i=1;i<nbPts();++i) {
      pt = evalAnimPt(get(i),frame);
      checkPoint[i].push_back(pt[0]);
      checkPoint[i].push_back(pt[1]);
    }
    for(unsigned int i=1;i<nbPts()-1;++i) {
      double h;
      h = 1/N;
      vector< vector<double> > checkPt(2);
      checkPt[0] = checkPoint[i];
      checkPt[1] = checkPoint[i+1];
      H = hermiteInter(checkPt, h);
      for (int k(0); k<N; k++){
          p.lineTo(H[k][0],H[k][1]);
      }
  }
    return p;
  }
};


class Curve2DHermiteConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DHermiteConstructor()                     {}
  virtual const QString type() const                      { return "HermiteCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DHermite(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DHermite(c,name); }
};




#endif
