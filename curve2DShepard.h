#ifndef CURVE_2D_SHEPARD_H
#define CURVE_2D_SHEPARD_H

#include "curve2D.h"

class Curve2DShepard : public Curve2D {
 public:
 Curve2DShepard(const QString &name) : Curve2D(name) {}
 Curve2DShepard(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
  
  QPainterPath path(float frame) {
    QPainterPath p;
    if(nbPts()==0) 
      return p;

    Vector2f pt = evalAnimPt(get(0),frame);

    p.moveTo(pt[0],pt[1]);
    for(unsigned int i=1;i<nbPts();++i) {
      pt = evalAnimPt(get(i),frame);
      p.lineTo(pt[0],pt[1]);
    }
    return p;
  }
};


class Curve2DShepardConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DShepardConstructor()                     {}
  virtual const QString type() const                      { return "ShepardCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DShepard(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DShepard(c,name); }
};


#endif // CURVE_2D_SHEPARD_H
