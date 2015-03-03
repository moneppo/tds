#include "TocRoot.h"
#include "TocControls.h"

using namespace ci;
using namespace ci::app;
using namespace std;

// Acts as a event dispatcher for all other tocs. Meant to be placed at the root level

Toc::Ptr TocRoot::CreateRoot( ci::app::App* app ) {
    Toc::Ptr result = make_shared<TocRoot>(app);
    result->Ref = result;
    _Roots.push_back(result);
    return result;
}

TocRoot::TocRoot( App* app ) : Toc( app )
{
    
#if defined( CINDER_COCOA_TOUCH )
    mTouchesBegan = mApp->getWindow()->getSignalTouchesBegan()
    .connect(0, bind( &TocRoot::onTouchesBegan, this, placeholders::_1 ) );
    
    mTouchesMoved = mApp->getWindow()->getSignalTouchesMoved()
    .connect(0, bind( &TocRoot::onTouchesMoved, this, placeholders::_1 ) );
    
    mTouchesEnded = mApp->getWindow()->getSignalTouchesEnded()
    .connect(0, bind( &TocRoot::onTouchesEnded, this, placeholders::_1 ) );
#else // !CINDER_COCOA_TOUCH
    mDown = mApp->getWindow()->getSignalMouseDown()
    .connect(0, bind( &TocRoot::onPointerDown, this, placeholders::_1 ));
    
    mUp   = mApp->getWindow()->getSignalMouseUp()
    .connect(0,   bind( &TocRoot::onPointerUp,   this, placeholders::_1 ) );
    
    mMove = mApp->getWindow()->getSignalMouseMove()
    .connect(0, bind( &TocRoot::onPointerMove, this, placeholders::_1 ) );
    
    mDrag = mApp->getWindow()->getSignalMouseDrag()
    .connect(0, bind( &TocRoot::onPointerDrag, this, placeholders::_1 ) );
#endif // CINDER_COCOA_TOUCH
    
}

#if defined( CINDER_COCOA_TOUCH )

void TocRoot::onTouchesBegan( TouchEvent e )
{
    
    vector<TouchEvent::Touch> touches = e.getTouches();
    for( vector<TouchEvent::Touch>::iterator t = touches.begin(); t != touches.end(); t++ ) {
        TouchEvent::Touch touch = *t;
        for (Toc::List::iterator c = mChildren.begin(); c != mChildren.end(); c++) {
            Toc::Ptr toc = *c;
            vec2 p = touch.getPos();
            if (toc->Bounds.contains(p)) {
                MouseEvent me = MouseEvent( e.getWindow(), MouseEvent::LEFT_DOWN, p.x, p.y, 0, 0.0f, 0 );
                toc->onPointerDown(me);
                break;
            }
        }
    }
}

void TocRoot::onTouchesMoved( TouchEvent e )
{
    vector<TouchEvent::Touch> touches = e.getTouches();
    for( vector<TouchEvent::Touch>::iterator t = touches.begin(); t != touches.end(); t++ ) {
        TouchEvent::Touch touch = *t;
        for (Toc::List::iterator c = mChildren.begin(); c != mChildren.end(); c++) {
            Toc::Ptr toc = *c;
            vec2 p = touch.getPos();
            if (toc->Bounds.contains(p)) {
                MouseEvent me = MouseEvent( e.getWindow(), MouseEvent::LEFT_DOWN, p.x, p.y, 0, 0.0f, 0 );
                toc->onPointerDrag(me);
                break;
            }
        }
    }
}

void TocRoot::onTouchesEnded( TouchEvent e )
{
    vector<TouchEvent::Touch> touches = e.getTouches();
    for( vector<TouchEvent::Touch>::iterator t = touches.begin(); t != touches.end(); t++ ) {
        TouchEvent::Touch touch = *t;
        for (Toc::List::iterator c = mChildren.begin(); c != mChildren.end(); c++) {
            Toc::Ptr toc = *c;
            vec2 p = touch.getPos();
            if (toc->Bounds.contains(p)) {
                MouseEvent me = MouseEvent( e.getWindow(), MouseEvent::LEFT_DOWN, p.x, p.y, 0, 0.0f, 0 );
                toc->onPointerUp(me);
                break;
            }
        }
        
    }
}

#else // !CINDER_COCOA_TOUCH

void TocRoot::onPointerDown( MouseEvent event )
{
    PointerEvent pointerEvent;
    pointerEvent.localPosition = vec2(event.getPos()) - Position;
    pointerEvent.globalPosition = event.getPos();
    pointerEvent.parentPosition = event.getPos();
    pointerEvent.type = PointerEvent::Left;
    if ( Active() && Controls->onPointerDown( pointerEvent ) ) {
        return;
    }
    
    Toc::onPointerDown(pointerEvent);
}

void TocRoot::onPointerUp( MouseEvent event )
{
    PointerEvent pointerEvent;
    pointerEvent.localPosition = vec2(event.getPos()) - Position;
    pointerEvent.globalPosition = event.getPos();
    pointerEvent.parentPosition = event.getPos();
    pointerEvent.type = PointerEvent::Left;
    if ( Active() && Controls->onPointerUp( pointerEvent ) ) {
        return;
    }
    
    Toc::onPointerUp(pointerEvent);
}

void TocRoot::onPointerDrag( MouseEvent event )
{
    PointerEvent pointerEvent;
    pointerEvent.localPosition = vec2(event.getPos()) - Position;
    pointerEvent.globalPosition = event.getPos();
    pointerEvent.parentPosition = event.getPos();
    pointerEvent.type = PointerEvent::Left;
    if ( Active() && Controls->onPointerDrag( pointerEvent ) ) {
        return;
    }
    
    Toc::onPointerDrag(pointerEvent);
}

void TocRoot::onPointerMove( MouseEvent event )
{
    PointerEvent pointerEvent;
    pointerEvent.localPosition = vec2(event.getPos()) - Position;
    pointerEvent.globalPosition = event.getPos();
    pointerEvent.parentPosition = event.getPos();
    pointerEvent.type = PointerEvent::Left;
    if ( Active() && Controls->onPointerMove( pointerEvent ) ) {
        return;
    }
    
    Toc::onPointerMove(pointerEvent);
}

#endif // CINDER_COCOA_TOUCH

TocRoot::~TocRoot() {
}
