#ifndef cinder02_TocControls_h
#define cinder02_TocControls_h

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Path2d.h"
#include "cinder/gl/gl.h"
#include <list>
#include <stdio.h>

#include "Toc.h"

class Toc;

class TocControls {
    
public:
    TocControls(std::shared_ptr<Toc> master);
    bool onPointerDown( PointerEvent e );
    bool onPointerUp( PointerEvent e );
    bool onPointerDrag( PointerEvent e );
    bool onPointerMove( PointerEvent e );
    
    void Draw();
    void DrawHandle( ci::Color c );
    
    bool CheckAndInsert(ci::vec2 p, Toc::Ptr toc);
    
    bool inHandle( ci::vec2 p);
    bool inResize( ci::vec2 p);
private:
    std::shared_ptr<Toc> mMaster;
    bool mMoving;
    bool mResizing;
    bool mInsertHover;
    
    ci::Rectf mHandle;
    ci::Rectf mResize;
    
    ci::vec2 mStart;
};


#endif
