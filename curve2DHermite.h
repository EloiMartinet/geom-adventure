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

vector< vector <double> > hermiteInter(vector<double> const checkPoint_1, vector<double> const checkPoint_2, double h)
{
    unsigned int N = (int)(1/h);
    vector< vector<double> > H(N);
    //vector< vector<double> > li(N, (double ) 1);
    //vector<double> dy(1,N);
    //vector<double> x(N);
    //vector<double> y(N);
    double a = (checkPoint_2[1] - checkPoint_1[1])/(checkPoint_2[0] - checkPoint_1[0]);
    //double b = checkPoint_1[1] - a * checkPoint_1[0];
    /*
    x[0] = checkPoint_1[0];
    y[0] = a*x[0] + b;
    for (unsigned int i = 1; i < N; i++) {
      x[i] = x[i-1] + i/h;
      y[i] = a*x[i] + b;
    }*/
    /*
    dy[0] = (y[1] - y[0])/h;
    for (unsigned int i = 1; i < N-1; i++) {
      dy[i] = (y[i+1] - y[i-1])/(2*h);
    }
    dy[-1] = (y[-1] - y[-2])/h;
    */
    for (unsigned int t = 0; t < N; t++) {
      vector<double> v(2);
      double s = (double) t/N;
      double h1 = 2*pow(s, 3) - 3*pow(s, 2) + 1;
      double h2 = (-2)*pow(s, 3) + 3*pow(s, 2);
      double h3 = pow(s, 3) - 2*pow(s, 2) + s;
      double h4 = pow(s, 3) - pow(s, 2);
      for (size_t i = 0; i < 2; i++) {
        v[i] = h1*checkPoint_1[i] + h2*checkPoint_2[i] + h3*a + h4*a;
      }
      H[t] = v;
    }
    /*
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
    */
    return H;
}

  QPainterPath path(float frame) {
    QPainterPath p;
    double N(100);
    vector< vector<double> > checkPoint(nbPts());
    vector< vector<double> >  H(N);
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
      H = hermiteInter(checkPoint[i], checkPoint[i+1], h);
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
