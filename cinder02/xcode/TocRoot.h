
#ifndef cinder02_TocRoot_h
#define cinder02_TocRoot_h

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Path2d.h"
#include "cinder/gl/gl.h"
#include <list>
#include <stdio.h>

#include "Toc.h"

class TocRoot : public Toc {
public:
    typedef std::shared_ptr<TocRoot> Ptr;
    typedef std::list<TocRoot::Ptr> List;
    
    TocRoot( ci::app::App* app );
    virtual ~TocRoot();
    
#if defined( CINDER_COCOA_TOUCH )
    
    virtual void onTouchesBegan( ci::TouchEvent e );
    virtual void onTouchesMoved( ci::TouchEvent e );
    virtual void onTouchesEnded( ci::TouchEvent e );
    
    Toc::Ptr toToc();
    
private:
    ci::signals::scoped_connection mTouchesBegan, mTouchesMoved, mTouchesEnded;
    
#else // !CINDER_COCOA_TOUCH
    
    virtual void onPointerDown( cinder::app::MouseEvent e );
    virtual void onPointerUp( cinder::app::MouseEvent e );
    virtual void onPointerDrag( cinder::app::MouseEvent e );
    virtual void onPointerMove( cinder::app::MouseEvent e );
    
private:
    ci::signals::scoped_connection mDown, mUp, mMove, mDrag;
    
#endif // CINDER_COCOA_TOUCH
};


#endif
