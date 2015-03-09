//
//  PaintStroke.h
//  cinder02
//
//  Created by Michael Oneppo on 3/7/15.
//
//

#ifndef __cinder02__PaintStroke__
#define __cinder02__PaintStroke__

#include <stdio.h>
#include "cinder/Path2d.h"
#include "cinder/Shape2d.h"
#include "cinder/gl/gl.h"

#define WIDTH_SCALE 1000.0f
#define MIN(x, y) (x < y ? x : y)
#define CLAMP(v, l, h) (v < l ? l : (v > h ? h : v))

class PaintStroke {
public:
    typedef std::shared_ptr<PaintStroke> Ref;
    typedef std::list<Ref> List;
    
    PaintStroke() : mDirty(true) {}
    
    virtual ~PaintStroke() {}
    
    void AddPoint(ci::vec2 pt);
    
    void Draw();
protected:
    std::vector<ci::vec2> mPoints;

    ci::Path2d mPath;
    bool mDirty;
    float mLastT;
};

#endif /* defined(__cinder02__PaintStroke__) */
