#include "Toc.h"
#include "TocControls.h"
#include "TocRoot.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Toc* Toc::_Active = nullptr;
bool Toc::Dragging = false;

Toc::Toc( App* app ) :
    mApp( app ),
    Controls(make_shared<TocControls>(Toc::Ptr(this))),
    Bounds(100, 100, 200, 200)
{}

Toc::Toc( TocRoot::Ptr toc ) :
    ViewState(toc->ViewState),
    Bounds(toc->Bounds),
    Controls(toc->Controls),
    mChildren(toc->mChildren),
    mApp(toc->mApp)
{
    if (toc->Active()) {
        _Active = this;
    }
}

Toc::~Toc() {
}

void Toc::InsertToc(Toc::Ptr toc) {
    mChildren.push_back(toc);
}

void Toc::InsertToc( TocRoot::Ptr toc ) {
    Toc::Ptr t = make_shared<Toc>(toc);
    mChildren.push_back(t);
}

void Toc::Draw() {
    if ( Active() ) {
        gl::color( Color( 1.0f, 1.0f, 1.0f ) );
        gl::drawStrokedRect( Bounds );
        
        Controls->Draw();
    } else {
        gl::color( Color( 0.5f, 0.5f, 0.5f ) );
        gl::drawStrokedRect( Bounds );
        
        if (Dragging) {
            Controls->DrawHandle( Color(0.5f, 0.5f, 0.5f ) );
        }
    }
    
    for ( Toc::List::iterator it = mChildren.begin(); it != mChildren.end(); it++ ) {
        Toc::Ptr toc = *it;
        toc->Draw();
    }
}

void Toc::PopulateFromFile( string name ) {
    
}

void Toc::onPointerDown( MouseEvent e )
{
    vec2 p = e.getPos();
    for ( Toc::List::iterator it = mChildren.begin(); it != mChildren.end(); it++ ) {
        Toc::Ptr toc = *it;
        
        if ( toc->Active() && toc->Controls->onPointerDown( e ) ) {
            return;
        }
        
        if ( toc->Bounds.contains( p ) ) {
            e.setHandled( true );
            toc->onPointerDown( e );
            return;
        }
    }
    
    if (!Active() && Bounds.contains(e.getPos())) {
        _Active = this;
    }
}

void Toc::onPointerUp( MouseEvent e )
{
    vec2 p = e.getPos();
    for ( Toc::List::iterator it = mChildren.begin(); it != mChildren.end(); it++ ) {
        Toc::Ptr toc = *it;
        
        if (toc->Active() && toc->Controls->onPointerUp(e)) {
            return;
        }

        if ( toc->Bounds.contains( p ) ) {
            e.setHandled( true );
            toc->onPointerUp( e );
            return;
        }
    }
}

void Toc::onPointerDrag( MouseEvent e )
{
    vec2 p = e.getPos();
    for ( Toc::List::iterator it = mChildren.begin(); it != mChildren.end(); it++ ) {
        Toc::Ptr toc = *it;
        
        
        if ( toc->Active() && toc->Controls->onPointerDrag( e ) ) {
            return;
        }

        if ( toc->Bounds.contains( p ) ) {
            e.setHandled( true );
            toc->onPointerDrag( e );
            return;
        }
    }
}

void Toc::onPointerMove( MouseEvent e )
{
    vec2 p = e.getPos();
    for (Toc::List::iterator it = mChildren.begin(); it != mChildren.end(); it++) {
        Toc::Ptr toc = *it;
        
        if (toc->Active() && toc->Controls->onPointerMove(e)) {
            return;
        }

        if (toc->Bounds.contains(p)) {
            toc->onPointerMove(e);
            return;
        }
    }
}