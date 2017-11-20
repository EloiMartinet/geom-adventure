#ifndef CURVE_1D_Lagrange_H
#define CURVE_1D_Lagrange_H

#include "curve1D.h"

class Curve1DLagrange : public Curve1D {
 public:
 Curve1DLagrange(const QString &name) : Curve1D(name) {}
 Curve1DLagrange(Curve1D *curve,const QString &name) : Curve1D(curve,name) {}
  
  
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
    for(unsigned int i=1;i<nbPts();++i) {
      p.lineTo(_points[i][0],_points[i][1]);
    }

    // right part 
    if(xmax>_points[nbPts()-1][0]) {
      p.lineTo(xmax,_points[nbPts()-1][1]);
    }

    return p;
  }
  
  float clamp(float x, float lowerlimit, float upperlimit)
  {
      if (x < lowerlimit) x = lowerlimit;
      if (x > upperlimit) x = upperlimit;
      return x;
  }

  float smoothstep(float edge0, float edge1, float x)
  {
      // Scale, bias and saturate x to 0..1 range
      x = clamp((x - edge0)/(edge1 - edge0), 0.0, 1.0); 
      // Evaluate polynomial
      return x*x*(3 - 2*x);
  }



  float evalAt(float y) {
    // special cases 
    float x = smoothstep(0,1,y);

    if(empty()) return 0.0f;
    if(x<=_points[0][0]) return _points[0][1];
    if(x>=_points[nbPts()-1][0]) return _points[nbPts()-1][1];

    // linear interp
    for(unsigned int i=0;i<nbPts()-1;++i) {
      if(_points[i+1][0]>=x) {
  return _points[i][1]+(_points[i+1][1]-_points[i][1])*
    ((x-_points[i][0])/(_points[i+1][0]-_points[i][0]));
      }
    }
    return _points[0][1];
  }
};


class Curve1DLagrangeConstructor : public Curve1DConstructor {
 public:
  virtual ~Curve1DLagrangeConstructor()                     {}
  virtual const QString type() const                      { return "Lagrange interpolation";    }
  virtual Curve1D *create(const QString &name)            { return new Curve1DLagrange(name);   }
  virtual Curve1D *create(Curve1D *c,const QString &name) { return new Curve1DLagrange(c,name); }
};


#endif // CURVE_1D_Lagrange_H
