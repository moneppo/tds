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
    bool onPointerDown( cinder::app::MouseEvent e );
    bool onPointerUp( cinder::app::MouseEvent e );
    bool onPointerDrag( cinder::app::MouseEvent e );
    bool onPointerMove( cinder::app::MouseEvent e );
    
    void Draw();
    void DrawHandle( ci::Color c );
    
    bool inHandle( ci::vec2 p);
    
    void Update();
private:
    std::shared_ptr<Toc> mMaster;
    bool mMoving;
    bool mResizing;
    
    ci::Rectf mHandle;
    ci::Rectf mResize;
    
    ci::vec2 mRel;
};


#endif
