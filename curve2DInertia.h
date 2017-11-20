#ifndef CURVE_2D_INERTIA_H
#define CURVE_2D_INERTIA_H

#include "curve2D.h"

class Curve2DInertia : public Curve2D {
 public:
 Curve2DInertia(const QString &name) : Curve2D(name) {}
 Curve2DInertia(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
  
  QPainterPath path(float frame) {
    QPainterPath p;
    if(nbPts() < 2) 
      return p;

    unsigned int SAMPLE = 10;
    Vector2f pt1 = evalAnimPt(get(0),frame);
    Vector2f pt2 = evalAnimPt(get(1),frame);
    Vector2f pt1next = evalAnimPt(get(0),frame+1);
    Vector2f pt2next = evalAnimPt(get(1),frame+1);

    Vector2f ptdiscr;
    Vector2f speed;
    double t;

    p.moveTo(pt1[0],pt1[1]);
    for(unsigned int i=0;i<nbPts()+1;++i) {

      pt1 = evalAnimPt(get(i%nbPts()),frame);
      pt2 = evalAnimPt(get((i+1)%nbPts()),frame);

      pt1next = evalAnimPt(get(i%nbPts()),frame+1);
      pt2next = evalAnimPt(get((i+1)%nbPts()),frame+1);

      for(unsigned int j=0; j<=SAMPLE; ++j){
        double t = (double)j/SAMPLE;

        double linex = (1-t)*pt1[0]+t*pt2[0];
        double liney = (1-t)*pt1[1]+t*pt2[1];

        double linexnext = (1-t)*pt1next[0]+t*pt2next[0];
        double lineynext = (1-t)*pt1next[1]+t*pt2next[1];

        speed[0] = linexnext - linex;
        speed[1] = lineynext - liney;
 
        double perturbx = -20*t*(1-t)*speed[0];
        double perturby = -20*t*(1-t)*speed[1];

        ptdiscr[0] = linex + perturbx;
        ptdiscr[1] = liney + perturby;

        p.lineTo(ptdiscr[0],ptdiscr[1]);
      }
    }
    return p;

  }
};


class Curve2DInertiaConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DInertiaConstructor()                     {}
  virtual const QString type() const                      { return "InertiaCurve";            }
  virtual Curve2D *create(const QString &name)            { return new Curve2DInertia(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DInertia(c,name); }
};


#endif // CURVE_2D_INERTIA_H
