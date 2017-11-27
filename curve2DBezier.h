#ifndef CURVE_2D_BEZIER_H
#define CURVE_2D_BEZIER_H

#include "curve2D.h"
#include <vector>
#include <iostream>

using namespace std;

class Curve2DBezier : public Curve2D {
 public:
 Curve2DBezier(const QString &name) : Curve2D(name) {}
 Curve2DBezier(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}

vector< vector <double> > deCasteljau(vector< vector<double> > const checkPoint, double t)
{
    int nbLignes(checkPoint.size());
    int nbColonnes(checkPoint[0].size());
    vector< vector<double> > M(checkPoint);
    while (nbLignes > 1)
    {
        for (int i=0; i < nbLignes-1; i++)
        {
            for( int j=0; j < nbColonnes; j++)
            {
                M[i][j] = (1-t)*M[i][j] + t*M[i+1][j];
            }
        }
        nbLignes -= 1;
        M.pop_back();
    }
    return M;
}

  QPainterPath path(float frame) {
    QPainterPath p;
    double N(100);
    vector< vector<double> > checkPoint(nbPts());
    vector<double> M(2);
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
    for (int k(0); k<N+1; k++){
        double t;
        t = k/N;
        M[0] = deCasteljau(checkPoint, t)[0][0];
        M[1] = deCasteljau(checkPoint, t)[0][1];
        p.lineTo(M[0],M[1]);
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




#endif
