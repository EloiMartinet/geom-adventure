#ifndef CURVE_1D_Shepard_H
#define CURVE_1D_Shepard_H

#include "curve1D.h"

class Curve1DShepard : public Curve1D {
 public:
 Curve1DShepard(const QString &name) : Curve1D(name) {}
 Curve1DShepard(Curve1D *curve,const QString &name) : Curve1D(curve,name) {}
  
  float weight(float x, float y){
    return 1./((x-y)*(x-y));
  }

  float evalAt(float x) {
    
    double accuracy = 0.001;

    // special cases 
    if(empty()) return 0.0f;
    if(x<=_points[0][0]) return _points[0][1];
    if(x>=_points[nbPts()-1][0]) return _points[nbPts()-1][1];

    for(size_t i=0; i<nbPts(); ++i){
      if(abs(x - _points[i][0]) < accuracy){
        return _points[i][1];
      }
    }

    float sum = 0;
    float weightsum = 0;

    for(size_t i=0; i<nbPts(); ++i){
      weightsum += weight(_points[i][0],x);
    }

    for(size_t i=0; i<nbPts(); ++i){
      sum += _points[i][1]*weight(_points[i][0],x);
    }

    return sum/weightsum;
  }
  
  QPainterPath path(float xmin,float xmax) {
    QPainterPath p;

    // empty test 
    if(empty()) 
      return p;

    unsigned int SAMPLE = 100 ;
    float step = (xmax-xmin)/SAMPLE;
    float x = xmin;

    p.moveTo(xmin, _points[0][1]);

    for(unsigned int i=0; i<SAMPLE; ++i){
      x += step;
      p.lineTo(x, evalAt(x));
    }
    
    return p;
  }

};


class Curve1DShepardConstructor : public Curve1DConstructor {
 public:
  virtual ~Curve1DShepardConstructor()                   {}
  virtual const QString type() const                      { return "Shepard interpolation";    }
  virtual Curve1D *create(const QString &name)            { return new Curve1DShepard(name);   }
  virtual Curve1D *create(Curve1D *c,const QString &name) { return new Curve1DShepard(c,name); }
};


#endif // CURVE_1D_Shepard_H
